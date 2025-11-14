#include "../include/optimizer.hpp"
#include <iostream>


Optimizer::Optimizer() {}

// --- MAIN OPTIMIZE ENTRY POINT ---
void Optimizer::optimize(Program* root) {
    if (!root) return;
    constantTable.clear(); 
    
    // 1. Optimize individual statements (Folding, Unrolling)
    // We use a temporary vector to hold Statements because Program holds ASTNode*
    std::vector<Statement*> globalStmts;
    
    for (size_t i = 0; i < root->declarations.size(); ++i) {
        if (auto s = dynamic_cast<Statement*>(root->declarations[i])) {
            // Run the optimization logic (Folding/Unrolling)
            Statement* opt = optimizeStatement(s);
            if (opt) globalStmts.push_back(opt);
        }
    }

    // 2. FIX: Remove Empty Blocks created by unrolling/DCE
    cleanEmptyBlocks(globalStmts);

    // 3. Run Peephole (Cancellation + Fusion) on Global Scope
    // Now that empty blocks are gone, q[0].h() and q[0].h() will be adjacent!
    optimizePeephole(globalStmts);

    // 4. Write back to Program
    root->declarations.clear();
    for (auto s : globalStmts) {
        root->declarations.push_back((ASTNode*)s);
    }
}

void Optimizer::optimizeBlock(Block* block) {
    if (!block) return;
    
    std::vector<Statement*> newStmts;
    for (size_t i = 0; i < block->statements.size(); ++i) {
        Statement* optimized = optimizeStatement(block->statements[i]);
        
        // Flattening Logic (removes nested blocks created by unrolling)
        if (auto innerBlock = dynamic_cast<Block*>(optimized)) {
            bool hasDecls = false;
            for(auto s : innerBlock->statements) {
                if (dynamic_cast<VarDecl*>(s)) { hasDecls = true; break; }
            }
            if (!hasDecls) {
                for(auto s : innerBlock->statements) newStmts.push_back(s);
            } else {
                newStmts.push_back(optimized);
            }
        } else if (optimized) {
            newStmts.push_back(optimized);
        }
    }
    
    // FIX: Clean Empty Blocks before peephole
    cleanEmptyBlocks(newStmts);

    // Run Peephole
    optimizePeephole(newStmts);
    
    block->statements = newStmts;
}

bool Optimizer::isConstant(Expression* expr) {
    if (!expr) return false;
    return (dynamic_cast<IntLiteral*>(expr) || 
            dynamic_cast<FloatLiteral*>(expr) || 
            dynamic_cast<BoolLiteral*>(expr));
}

Expression* Optimizer::cloneLiteral(Expression* lit) {
    if (auto i = dynamic_cast<IntLiteral*>(lit)) return (Expression*)(new IntLiteral(i->value))->loc(lit->line, lit->col);
    if (auto f = dynamic_cast<FloatLiteral*>(lit)) return (Expression*)(new FloatLiteral(f->value))->loc(lit->line, lit->col);
    if (auto b = dynamic_cast<BoolLiteral*>(lit)) return (Expression*)(new BoolLiteral(b->value))->loc(lit->line, lit->col);
    return nullptr;
}

Expression* Optimizer::foldBinary(BinaryExpr* expr, Expression* left, Expression* right) {
    int line = expr->line;
    int col = expr->col;

    if (auto l = dynamic_cast<BoolLiteral*>(left)) {
        if (auto r = dynamic_cast<BoolLiteral*>(right)) {
            switch(expr->op) {
                case OpType::AND: return (Expression*)(new BoolLiteral(l->value && r->value))->loc(line, col);
                case OpType::OR: return (Expression*)(new BoolLiteral(l->value || r->value))->loc(line, col);
                case OpType::EQ: return (Expression*)(new BoolLiteral(l->value == r->value))->loc(line, col);
                case OpType::NEQ: return (Expression*)(new BoolLiteral(l->value != r->value))->loc(line, col);
                default: return expr;
            }
        }
    }
    if (auto l = dynamic_cast<IntLiteral*>(left)) {
        if (auto r = dynamic_cast<IntLiteral*>(right)) {
            int result = 0;
            switch (expr->op) {
                case OpType::PLUS: return (Expression*)(new IntLiteral(l->value + r->value))->loc(line, col);
                case OpType::MINUS: return (Expression*)(new IntLiteral(l->value - r->value))->loc(line, col);
                case OpType::MUL: return (Expression*)(new IntLiteral(l->value * r->value))->loc(line, col);
                case OpType::DIV: return (Expression*)(new IntLiteral((r->value != 0) ? l->value / r->value : 0))->loc(line, col);
                case OpType::POWER: return (Expression*)(new IntLiteral(std::pow(l->value, r->value)))->loc(line, col);
                case OpType::LT: return (Expression*)(new BoolLiteral(l->value < r->value))->loc(line, col);
                case OpType::GT: return (Expression*)(new BoolLiteral(l->value > r->value))->loc(line, col);
                case OpType::LTE: return (Expression*)(new BoolLiteral(l->value <= r->value))->loc(line, col);
                case OpType::GTE: return (Expression*)(new BoolLiteral(l->value >= r->value))->loc(line, col);
                case OpType::EQ: return (Expression*)(new BoolLiteral(l->value == r->value))->loc(line, col);
                case OpType::NEQ: return (Expression*)(new BoolLiteral(l->value != r->value))->loc(line, col);
                case OpType::LSHIFT: return (Expression*)(new IntLiteral(l->value << r->value))->loc(line, col);
                case OpType::RSHIFT: return (Expression*)(new IntLiteral(l->value >> r->value))->loc(line, col);
                case OpType::AND: return (Expression*)(new BoolLiteral((bool)l->value && (bool)r->value))->loc(line, col);
                case OpType::OR: return (Expression*)(new BoolLiteral((bool)l->value || (bool)r->value))->loc(line, col);
                default: return expr; 
            }
        }
        else if (auto rF = dynamic_cast<FloatLiteral*>(right)) {
            double valL = (double)l->value;
            double valR = rF->value;
            switch(expr->op) {
                case OpType::PLUS: return (Expression*)(new FloatLiteral(valL + valR))->loc(line, col);
                case OpType::MINUS: return (Expression*)(new FloatLiteral(valL - valR))->loc(line, col);
                case OpType::MUL: return (Expression*)(new FloatLiteral(valL * valR))->loc(line, col);
                case OpType::DIV: return (Expression*)(new FloatLiteral(valL / valR))->loc(line, col);
                case OpType::POWER: return (Expression*)(new FloatLiteral(std::pow(valL, valR)))->loc(line, col);
                default: return expr;
            }
        }
    }
    else if (auto l = dynamic_cast<FloatLiteral*>(left)) {
        double valL = l->value;
        double valR = 0.0;
        
        if (auto rInt = dynamic_cast<IntLiteral*>(right)) valR = (double)rInt->value;
        else if (auto rF = dynamic_cast<FloatLiteral*>(right)) valR = rF->value;
        else return expr;

        switch (expr->op) {
            case OpType::PLUS: return (Expression*)(new FloatLiteral(valL + valR))->loc(line, col);
            case OpType::MINUS: return (Expression*)(new FloatLiteral(valL - valR))->loc(line, col);
            case OpType::MUL: return (Expression*)(new FloatLiteral(valL * valR))->loc(line, col);
            case OpType::DIV: return (Expression*)(new FloatLiteral(valL / valR))->loc(line, col);
            case OpType::POWER: return (Expression*)(new FloatLiteral(std::pow(valL, valR)))->loc(line, col);
            default: return expr;
        }
    }

    return expr;
}

bool Optimizer::isSelfInverse(const std::string& name) {
    return (name == "h" || name == "x" || name == "y" || name == "z" || 
            name == "cnot" || name == "cx" || name == "cz");
}

bool Optimizer::isRotation(const std::string& name) {
    return (name == "rx" || name == "ry" || name == "rz" || name == "p" || name == "rzz");
}

bool Optimizer::areExpressionsEqual(Expression* a, Expression* b) {
    if (a == b) return true;
    if (!a || !b) return false;

    if (auto idA = dynamic_cast<Identifier*>(a)) {
        if (auto idB = dynamic_cast<Identifier*>(b)) return idA->name == idB->name;
    }
    else if (auto iA = dynamic_cast<IntLiteral*>(a)) {
        if (auto iB = dynamic_cast<IntLiteral*>(b)) return iA->value == iB->value;
    }
    else if (auto fA = dynamic_cast<FloatLiteral*>(a)) {
        if (auto fB = dynamic_cast<FloatLiteral*>(b)) return fA->value == fB->value;
    }
    else if (auto idxA = dynamic_cast<IndexExpr*>(a)) {
        if (auto idxB = dynamic_cast<IndexExpr*>(b)) {
            return areExpressionsEqual(idxA->array, idxB->array) &&
                   areExpressionsEqual(idxA->index, idxB->index);
        }
    }
    return false;
}