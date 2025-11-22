#include "../include/codegen.hpp"
#include <iostream>

void CodeGenerator::generate(Program* root) {
    if (!root) return;

    out << "OPENQASM 3.0;\n";
    out << "include \"stdgates.inc\";\n\n";

    for (ASTNode* decl : root->declarations) {
        if (auto s = dynamic_cast<Statement*>(decl)) {
            visitStatement(s);
        }
    }
}

void CodeGenerator::emitIndent() {
    for (int i = 0; i < indentLevel; ++i) out << "    ";
}

void CodeGenerator::visitBlock(Block* block) {
    out << "{\n";
    indentLevel++;
    for (Statement* stmt : block->statements) {
        visitStatement(stmt);
    }
    indentLevel--;
    emitIndent();
    out << "}";
}

void CodeGenerator::visitStatement(Statement* stmt) {
    if (!stmt) return;

    if (auto decl = dynamic_cast<VarDecl*>(stmt)) {
        emitIndent();
        
        if (decl->type.baseType == DataType::QUBIT) {
            out << "qubit";
            if (decl->arraySizeExpr) {
                out << "[";
                visitExpression(decl->arraySizeExpr);
                out << "]";
            }
            out << " " << decl->name;
        } 
        else if (decl->type.baseType == DataType::BIT) {
            out << "bit";
            if (decl->arraySizeExpr) {
                out << "[";
                visitExpression(decl->arraySizeExpr);
                out << "]";
            }
            out << " " << decl->name;
        }
        else {
            if (decl->isConst) out << "const ";
            
            switch(decl->type.baseType) {
                case DataType::INT: out << "int[32]"; break;
                case DataType::FLOAT: out << "float[64]"; break;
                case DataType::ANGLE: out << "angle[32]"; break;
                case DataType::BOOL: out << "bool"; break;
                case DataType::COMPLEX: out << "complex[64]"; break;
                default: out << "let"; break;
            }
            
            if (decl->arraySizeExpr) {
                out << "[";
                visitExpression(decl->arraySizeExpr);
                out << "]";
            }

            out << " " << decl->name;
            
            if (decl->initializer) {
                out << " = ";
                visitExpression(decl->initializer);
            }
        }
        out << ";\n";
    }
    else if (auto ifStmt = dynamic_cast<IfStmt*>(stmt)) {
        emitIndent();
        out << "if (";
        visitExpression(ifStmt->condition);
        out << ") ";
        visitBlock(ifStmt->thenBlock);
        
        if (ifStmt->elseBlock) {
            out << " else ";
            if (dynamic_cast<Block*>(ifStmt->elseBlock)) {
                visitBlock((Block*)ifStmt->elseBlock);
            } else {
                visitStatement(ifStmt->elseBlock);
            }
        }
        out << "\n";
    }
    else if (auto loop = dynamic_cast<ForStmt*>(stmt)) {
        emitIndent();
        out << "for int " << loop->iterator << " in [";
        
        if (auto rng = dynamic_cast<RangeExpr*>(loop->iterable)) {
            visitExpression(rng->start);
            out << ":";
            visitExpression(rng->end);
        } else {
            visitExpression(loop->iterable);
        }
        out << "] ";
        visitBlock(loop->body);
        out << "\n";
    }
    else if (auto whileStmt = dynamic_cast<WhileStmt*>(stmt)) {
        emitIndent();
        out << "while (";
        visitExpression(whileStmt->condition);
        out << ") ";
        visitBlock(whileStmt->body);
        out << "\n";
    }
    else if (auto func = dynamic_cast<FuncDecl*>(stmt)) {
        emitIndent();
        out << "def " << func->name << "(";
        for (size_t i = 0; i < func->params.size(); ++i) {
            out << "int[32] " << func->params[i].name; 
            if (i < func->params.size() - 1) out << ", ";
        }
        out << ") ";
        visitBlock(func->body);
        out << "\n";
    }
    else if (auto delay = dynamic_cast<DelayStmt*>(stmt)) {
        emitIndent();
        out << "delay[";
        visitExpression(delay->duration);
        out << "] ";
        visitExpression(delay->target);
        out << ";\n";
    }
    else if (auto barrier = dynamic_cast<BarrierStmt*>(stmt)) {
        emitIndent();
        out << "barrier;\n"; 
    }
    // --- FIXED PARALLEL BLOCK ---
    else if (auto par = dynamic_cast<ParallelStmt*>(stmt)) {
        emitIndent();
        
        // 1. Handle modifiers (box/stretch)
        if (par->mode == "box") out << "box ";
        
        // 2. Print the block content
        // We manually traverse the block to inject the barrier INSIDE
        out << "{\n";
        indentLevel++;
        for (Statement* s : par->body->statements) {
            visitStatement(s);
        }
        
        // 3. AUTOMATIC BARRIER
        // We emit a global barrier at the end of the parallel block
        // to ensure all threads/qubits synchronize before moving on.
        emitIndent();
        out << "barrier;\n";
        
        indentLevel--;
        emitIndent();
        out << "}\n";
    }
    else if (auto exprStmt = dynamic_cast<ExprStmt*>(stmt)) {
        emitIndent();
        visitExpression(exprStmt->expr);
        out << ";\n";
    }
    else if (auto block = dynamic_cast<Block*>(stmt)) {
        emitIndent();
        visitBlock(block);
        out << "\n";
    }
}