#include "../include/semantic.hpp"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer() : hasError(false) {}

bool SemanticAnalyzer::analyze(Program* root) {
    hasError = false;
    if (!root) return false;
    checkProgram(root);
    return !hasError;
}

void SemanticAnalyzer::error(ASTNode* node, const std::string& msg) {
    std::cerr << "[Semantic Error] Line " << (node ? node->line : 0) 
              << ", Col " << (node ? node->col : 0) 
              << ": " << msg << std::endl;
    hasError = true;
}

// Helpers

std::string SemanticAnalyzer::typeToString(DataType t) {
    switch(t) {
        case DataType::INT: return "int";
        case DataType::FLOAT: return "float";
        case DataType::BOOL: return "bool";
        case DataType::QUBIT: return "qubit";
        case DataType::BIT: return "bit";
        case DataType::VOID: return "void";
        case DataType::ANGLE: return "angle";
        case DataType::COMPLEX: return "complex";
        case DataType::MATRIX: return "matrix";
        case DataType::STRING: return "string";
        case DataType::AUTO: return "auto";
        default: return "unknown";
    }
}

bool SemanticAnalyzer::isQuantumType(DataType t) {
    return t == DataType::QUBIT;
}

bool SemanticAnalyzer::isNumber(DataType t) {
    return t == DataType::INT || t == DataType::FLOAT || t == DataType::ANGLE || t == DataType::COMPLEX;
}

// Traversal

void SemanticAnalyzer::checkProgram(Program* node) {
    for (ASTNode* decl : node->declarations) {
        if (auto d = dynamic_cast<VarDecl*>(decl)) checkVarDecl(d);
        else if (auto f = dynamic_cast<FuncDecl*>(decl)) checkFuncDecl(f);
        else if (auto s = dynamic_cast<Statement*>(decl)) checkStatement(s);
    }
}

void SemanticAnalyzer::checkBlock(Block* block) {
    symTable.enterScope();
    for (Statement* stmt : block->statements) {
        checkStatement(stmt);
    }
    symTable.exitScope();
}

void SemanticAnalyzer::checkStatement(Statement* stmt) {
    if (auto v = dynamic_cast<VarDecl*>(stmt)) {
        checkVarDecl(v);
    }
    else if (auto e = dynamic_cast<ExprStmt*>(stmt)) {
        checkExpression(e->expr);
    }
    else if (auto b = dynamic_cast<Block*>(stmt)) {
        checkBlock(b);
    }
    else if (auto i = dynamic_cast<IfStmt*>(stmt)) {
        DataType condType = checkExpression(i->condition);
        if (condType != DataType::BOOL && condType != DataType::INT) {
            error(i->condition, "'if' condition must be boolean or int");
        }
        checkBlock(i->thenBlock);
        if (i->elseBlock) checkStatement(i->elseBlock);
    }
    else if (auto w = dynamic_cast<WhileStmt*>(stmt)) {
        DataType condType = checkExpression(w->condition);
        if (condType != DataType::BOOL && condType != DataType::INT) {
            error(w->condition, "'while' condition must be boolean or int");
        }
        checkBlock(w->body);
    }
    else if (auto f = dynamic_cast<ForStmt*>(stmt)) {
        symTable.enterScope();
        
        DataType iterType = DataType::INT; // Default for ranges
        bool validIterable = false;

        // 1. Check what we are iterating over
        if (auto rng = dynamic_cast<RangeExpr*>(f->iterable)) {
            checkExpression(rng);
            iterType = DataType::INT;
            validIterable = true;
        }
        else if (auto id = dynamic_cast<Identifier*>(f->iterable)) {
            // Look up the variable to check if it is an array
            SymbolInfo* sym = symTable.lookup(id->name);
            if (sym) {
                if (sym->isArray) {
                    iterType = sym->type; // e.g., float array -> float iterator
                    validIterable = true;
                } else {
                    error(f->iterable, "Cannot iterate over scalar variable '" + id->name + "'");
                }
            } else {
                error(f->iterable, "Undefined variable '" + id->name + "'");
            }
        }
        else if (auto arr = dynamic_cast<ArrayLiteral*>(f->iterable)) {
            // Infer type from the array literal (e.g. [1.0, 2.0] -> FLOAT)
            iterType = checkExpression(arr);
            validIterable = true;
        }
        else {
            // Fallback check
            checkExpression(f->iterable); 
            error(f->iterable, "Invalid iterable expression in for-loop");
        }

        // 2. Declare the iterator with the INFERRED type
        // (Only if iterable was valid, otherwise default to INT to suppress cascade errors)
        SymbolInfo iter = { f->iterator, iterType, false, 0, false, false, {} };
        if (!symTable.declare(iter)) {
             error(f->iterable, "Loop iterator '" + f->iterator + "' redeclared");
        }
        
        // 3. Check Body
        checkBlock(f->body);
        symTable.exitScope();
    }
    else if (auto p = dynamic_cast<ParallelStmt*>(stmt)) {
        checkBlock(p->body);
    }
    else if (auto d = dynamic_cast<DelayStmt*>(stmt)) {
        DataType t = checkExpression(d->target);
        if (t != DataType::QUBIT) {
            error(d->target, "Delay target must be a qubit");
        }
    }
}

// Declarations

void SemanticAnalyzer::checkVarDecl(VarDecl* decl) {
    DataType inferredType = DataType::VOID;
    if (decl->initializer) {
        inferredType = checkExpression(decl->initializer);
    }

    // Check if this is a quantum array allocation (e.g., qubit q[5])
    bool isQuantumAlloc = decl->type.isArray && 
                          (decl->type.baseType == DataType::QUBIT || decl->type.baseType == DataType::BIT);

    if (decl->type.baseType == DataType::AUTO) {
        if (decl->initializer == nullptr) {
            error(decl, "Variable '" + decl->name + "' declared with 'var/alias' must have an initializer.");
            return;
        }
        decl->type.baseType = inferredType;
    } 
    else if (isQuantumAlloc) {
        // Size check for qubits (stored in arraySizeExpr)
        if (decl->arraySizeExpr) {
            if (checkExpression(decl->arraySizeExpr) != DataType::INT) {
                error(decl->arraySizeExpr, "Array size for '" + decl->name + "' must be an integer.");
            }
        }
    }
    else {
        // Standard Assignment Check
        if (decl->initializer && decl->type.baseType != inferredType) {
            bool safe = false;
            // --- IMPLICIT CASTING RULES ---
            if (decl->type.baseType == inferredType) safe = true;
            // Int -> Float
            if (decl->type.baseType == DataType::FLOAT && inferredType == DataType::INT) safe = true;
            // Int -> Angle
            if (decl->type.baseType == DataType::ANGLE && inferredType == DataType::INT) safe = true;
            // Float -> Angle (THIS IS THE FIX YOU NEED)
            if (decl->type.baseType == DataType::ANGLE && inferredType == DataType::FLOAT) safe = true;
            // Numbers -> Complex
            if (decl->type.baseType == DataType::COMPLEX && inferredType == DataType::INT) safe = true;
            if (decl->type.baseType == DataType::COMPLEX && inferredType == DataType::FLOAT) safe = true;

            if (!safe) {
                error(decl, "Type mismatch in declaration of '" + decl->name + "'. Expected " + 
                      typeToString(decl->type.baseType) + ", got " + typeToString(inferredType));
            }
        }
    }

    SymbolInfo info;
    info.name = decl->name;
    info.type = decl->type.baseType;
    info.isArray = decl->type.isArray;
    info.isConst = decl->isConst;
    info.isFunction = false;
    
    // Register Array Size logic
    if (decl->arraySizeExpr) {
         if (auto lit = dynamic_cast<IntLiteral*>(decl->arraySizeExpr)) {
             info.arraySize = lit->value;
         }
    } else if (!decl->type.dimensions.empty()) {
        info.arraySize = decl->type.dimensions[0]; 
    } else if (decl->initializer && dynamic_cast<ArrayLiteral*>(decl->initializer)) {
        info.arraySize = dynamic_cast<ArrayLiteral*>(decl->initializer)->elements.size();
        info.isArray = true;
    }

    if (!symTable.declare(info)) {
        error(decl, "Variable '" + decl->name + "' is already declared in this scope.");
    }
}

void SemanticAnalyzer::checkFuncDecl(FuncDecl* decl) {
    // 1. Register Function Name in Outer Scope
    SymbolInfo funcInfo;
    funcInfo.name = decl->name;
    funcInfo.type = DataType::VOID;
    funcInfo.isFunction = true;
    
    // Store param types for future call checking (optional but good practice)
    for(const auto& p : decl->params) {
        funcInfo.paramTypes.push_back(p.type.baseType);
    }

    if (!symTable.declare(funcInfo)) {
        error(decl, "Function/Circuit '" + decl->name + "' redeclared.");
    }

    // 2. Enter Function Scope
    symTable.enterScope();

    // 3. FIX: Register Parameters as Local Variables
    for (const auto& param : decl->params) {
        SymbolInfo pInfo;
        pInfo.name = param.name;
        pInfo.type = param.type.baseType;
        pInfo.isArray = param.type.isArray;
        pInfo.isConst = false;
        pInfo.isFunction = false;
        
        if (!symTable.declare(pInfo)) {
            error(decl, "Parameter '" + param.name + "' redeclared.");
        }
    }

    // 4. Check Body
    checkBlock(decl->body);

    // 5. Exit Scope
    symTable.exitScope();
}