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

// =========================================================
// Helpers
// =========================================================

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

// =========================================================
// Traversal
// =========================================================

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

// =========================================================
// Declarations
// =========================================================

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

// =========================================================
// Expressions
// =========================================================

DataType SemanticAnalyzer::checkExpression(Expression* expr) {
    if (!expr) return DataType::VOID;

    if (auto i = dynamic_cast<IntLiteral*>(expr)) return DataType::INT;
    if (auto f = dynamic_cast<FloatLiteral*>(expr)) return DataType::FLOAT;
    if (auto b = dynamic_cast<BoolLiteral*>(expr)) return DataType::BOOL;
    if (auto s = dynamic_cast<StringLiteral*>(expr)) return DataType::STRING;
    if (auto im = dynamic_cast<ImaginaryLiteral*>(expr)) return DataType::COMPLEX;
    
    if (auto id = dynamic_cast<Identifier*>(expr)) return checkIdentifier(id);
    if (auto bin = dynamic_cast<BinaryExpr*>(expr)) return checkBinary(bin);
    if (auto m = dynamic_cast<MethodCallExpr*>(expr)) return checkMethodCall(m);
    if (auto c = dynamic_cast<CallExpr*>(expr)) return checkCall(c);
    
    if (auto idx = dynamic_cast<IndexExpr*>(expr)) {
        DataType base = checkExpression(idx->array);
        checkExpression(idx->index); 
        if (base == DataType::QUBIT) return DataType::QUBIT;
        if (base == DataType::BIT) return DataType::BIT;
        return base; 
    }
    
    if (auto arr = dynamic_cast<ArrayLiteral*>(expr)) {
        if (!arr->elements.empty()) {
            // Check for Matrix (Nested Array)
            if (dynamic_cast<ArrayLiteral*>(arr->elements[0])) {
                return DataType::MATRIX;
            }
            return checkExpression(arr->elements[0]);
        }
        return DataType::INT;
    }
    
    if (auto rng = dynamic_cast<RangeExpr*>(expr)) {
        checkExpression(rng->start);
        checkExpression(rng->end);
        return DataType::INT;
    }

    return DataType::VOID;
}

DataType SemanticAnalyzer::checkIdentifier(Identifier* id) {
    SymbolInfo* sym = symTable.lookup(id->name);
    if (!sym) {
        error(id, "Undefined variable '" + id->name + "'");
        return DataType::VOID;
    }
    return sym->type;
}

DataType SemanticAnalyzer::checkCall(CallExpr* expr) {
    SymbolInfo* sym = symTable.lookup(expr->callee);
    
    if (!sym) {
        error(expr, "Undefined function '" + expr->callee + "'");
        return DataType::VOID;
    }

    if (!sym->isFunction) {
        error(expr, "'" + expr->callee + "' is not a function");
        return DataType::VOID;
    }

    for (auto arg : expr->args) {
        checkExpression(arg);
    }

    return sym->type; 
}

DataType SemanticAnalyzer::checkBinary(BinaryExpr* expr) {
    DataType lhs = checkExpression(expr->left);
    DataType rhs = checkExpression(expr->right);

    // 1. Assignment
    if (expr->op == OpType::ASSIGN || 
        expr->op == OpType::PLUS_ASSIGN || 
        expr->op == OpType::MINUS_ASSIGN) {
        
        if (lhs == DataType::QUBIT || lhs == DataType::BIT) {
            if (lhs == DataType::BIT && rhs == DataType::INT) return DataType::BIT;
        }
        
        if (lhs != rhs && lhs != DataType::VOID && rhs != DataType::VOID) {
             // Allow implicit casting logic
             if (lhs == DataType::FLOAT && rhs == DataType::INT) return DataType::FLOAT;
             if (lhs == DataType::COMPLEX && rhs == DataType::FLOAT) return DataType::COMPLEX;
             if (lhs == DataType::ANGLE && rhs == DataType::FLOAT) return DataType::ANGLE; // Angle = Float
             error(expr, "Type mismatch in assignment");
        }
        return lhs;
    }

    // 2. Logical
    if (expr->op == OpType::AND || expr->op == OpType::OR) {
        bool lhsValid = (lhs == DataType::BOOL || lhs == DataType::INT);
        bool rhsValid = (rhs == DataType::BOOL || rhs == DataType::INT);
        if (!lhsValid || !rhsValid) {
            error(expr, "Logical AND/OR requires boolean or integer operands");
        }
        return DataType::BOOL;
    }

    // 3. Relational
    if (expr->op >= OpType::EQ && expr->op <= OpType::GTE) {
        return DataType::BOOL;
    }

    // 4. Arithmetic
    if (lhs == DataType::INT && rhs == DataType::INT) return DataType::INT;
    if ((lhs == DataType::FLOAT || rhs == DataType::FLOAT) && isNumber(lhs) && isNumber(rhs)) return DataType::FLOAT;
    if ((lhs == DataType::COMPLEX || rhs == DataType::COMPLEX) && isNumber(lhs) && isNumber(rhs)) return DataType::COMPLEX;

    return lhs;
}

DataType SemanticAnalyzer::checkMethodCall(MethodCallExpr* expr) {
    DataType objType = checkExpression(expr->object);
    std::string method = expr->method;

    if (objType == DataType::QUBIT) {
        if (method == "h" || method == "x" || method == "y" || method == "z") {
            if (!expr->args.empty()) error(expr, "Gate '" + method + "' expects 0 arguments");
            return DataType::QUBIT;
        }
        else if (method == "rx" || method == "ry" || method == "rz" || method == "p") {
            if (expr->args.size() != 1) error(expr, "Rotation '" + method + "' expects 1 angle argument");
            else {
                 DataType argT = checkExpression(expr->args[0]);
                 // FIX: Allow ANY number type (Int, Float, Angle)
                 if (!isNumber(argT)) error(expr->args[0], "Rotation argument must be a number/angle");
            }
            return DataType::QUBIT;
        }
        else if (method == "cnot" || method == "cx") {
            if (expr->args.size() != 1) error(expr, "CNOT expects 1 control argument");
            else {
                if (checkExpression(expr->args[0]) != DataType::QUBIT) error(expr->args[0], "CNOT control must be a qubit");
            }
            return DataType::QUBIT;
        }
        else if (method == "mcx" || method == "mcz") {
            if (expr->args.empty()) {
                error(expr, "Multi-control gate '" + method + "' requires at least 1 control qubit");
            }
            for (size_t i = 0; i < expr->args.size(); i++) {
                DataType t = checkExpression(expr->args[i]);
                if (t != DataType::QUBIT) {
                    error(expr->args[i], "Argument " + std::to_string(i+1) + " of '" + method + "' must be a qubit");
                }
            }
            return DataType::QUBIT; 
        }
        else if (method == "measure") {
            return DataType::INT; 
        }
        else {
            error(expr, "Unknown quantum method '" + method + "'");
        }
    } 
    return DataType::VOID;
}