#include "../include/optimizer.hpp"
#include <iostream>

// --- HELPER TO REMOVE EMPTY BLOCKS ---
// Recursively removes empty blocks from a list of statements.
// This is important for cleaning up after loop unrolling so that adjacent
// gates (separated by empty loop blocks) can be cancelled.
void cleanEmptyBlocks(std::vector<Statement *> &stmts)
{
    std::vector<Statement *> cleaned;
    for (auto s : stmts)
    {
        if (auto block = dynamic_cast<Block *>(s))
        {
            // Recursively clean the inner block first
            cleanEmptyBlocks(block->statements);

            // If the block is now empty, skip it (deleting it)
            if (block->statements.empty())
            {
                continue;
            }
        }
        cleaned.push_back(s);
    }
    stmts = cleaned;
}

Optimizer::Optimizer() {}

void Optimizer::optimize(Program *root)
{
    if (!root)
        return;
    constantTable.clear();

    // We use a temporary vector to hold Statements because Program holds ASTNode*
    std::vector<Statement *> globalStmts;

    for (size_t i = 0; i < root->declarations.size(); ++i)
    {
        if (auto s = dynamic_cast<Statement *>(root->declarations[i]))
        {
            // Run the optimization logic (Folding/Unrolling)
            Statement *opt = optimizeStatement(s);
            if (opt)
                globalStmts.push_back(opt);
        }
    }

    cleanEmptyBlocks(globalStmts);

    // Now that empty blocks are gone, q[0].h() and q[0].h() will be adjacent!
    optimizePeephole(globalStmts);

    root->declarations.clear();
    for (auto s : globalStmts)
    {
        root->declarations.push_back((ASTNode *)s);
    }
}

void Optimizer::optimizeBlock(Block *block)
{
    if (!block)
        return;

    std::vector<Statement *> newStmts;
    for (size_t i = 0; i < block->statements.size(); ++i)
    {
        Statement *optimized = optimizeStatement(block->statements[i]);

        // Flattening Logic (removes nested blocks created by unrolling)
        if (auto innerBlock = dynamic_cast<Block *>(optimized))
        {
            bool hasDecls = false;
            for (auto s : innerBlock->statements)
            {
                if (dynamic_cast<VarDecl *>(s))
                {
                    hasDecls = true;
                    break;
                }
            }
            if (!hasDecls)
            {
                for (auto s : innerBlock->statements)
                    newStmts.push_back(s);
            }
            else
            {
                newStmts.push_back(optimized);
            }
        }
        else if (optimized)
        {
            newStmts.push_back(optimized);
        }
    }

    cleanEmptyBlocks(newStmts);

    optimizePeephole(newStmts);

    block->statements = newStmts;
}

Statement *Optimizer::optimizeStatement(Statement *stmt)
{
    if (!stmt)
        return nullptr;

    if (auto decl = dynamic_cast<VarDecl *>(stmt))
    {
        if (decl->initializer)
        {
            decl->initializer = optimizeExpression(decl->initializer);
            if (decl->isConst && isConstant(decl->initializer))
            {
                constantTable[decl->name] = decl->initializer;
            }
        }
        if (decl->arraySizeExpr)
        {
            decl->arraySizeExpr = optimizeExpression(decl->arraySizeExpr);
        }
        return decl;
    }
    else if (auto exprStmt = dynamic_cast<ExprStmt *>(stmt))
    {
        exprStmt->expr = optimizeExpression(exprStmt->expr);
        return exprStmt;
    }
    else if (auto block = dynamic_cast<Block *>(stmt))
    {
        optimizeBlock(block);
        return block;
    }
    else if (auto ifStmt = dynamic_cast<IfStmt *>(stmt))
    {
        ifStmt->condition = optimizeExpression(ifStmt->condition);
        optimizeBlock(ifStmt->thenBlock);
        if (ifStmt->elseBlock)
            ifStmt->elseBlock = optimizeStatement(ifStmt->elseBlock);

        if (auto boolLit = dynamic_cast<BoolLiteral *>(ifStmt->condition))
        {
            if (boolLit->value == false)
            {
                return ifStmt->elseBlock ? ifStmt->elseBlock : new Block();
            }
        }
        return ifStmt;
    }
    else if (auto loop = dynamic_cast<ForStmt *>(stmt))
    {
        loop->iterable = optimizeExpression(loop->iterable);

        if (auto rng = dynamic_cast<RangeExpr *>(loop->iterable))
        {
            if (auto startLit = dynamic_cast<IntLiteral *>(rng->start))
            {
                if (auto endLit = dynamic_cast<IntLiteral *>(rng->end))
                {

                    Block *unrolledBlock = new Block();
                    int start = startLit->value;
                    int end = endLit->value;

                    if (end - start < 100)
                    {
                        for (int k = start; k <= end; ++k)
                        {

                            Expression *oldVal = nullptr;
                            if (constantTable.count(loop->iterator))
                                oldVal = constantTable[loop->iterator];

                            // Cast generic ASTNode* to Expression* for constantTable
                            constantTable[loop->iterator] = (Expression *)(new IntLiteral(k))->loc(loop->line, loop->col);

                            Block *bodyClone = (Block *)loop->body->clone();
                            optimizeBlock(bodyClone);

                            for (auto s : bodyClone->statements)
                            {
                                unrolledBlock->add(s);
                            }

                            if (oldVal)
                                constantTable[loop->iterator] = oldVal;
                            else
                                constantTable.erase(loop->iterator);
                        }

                        // Recursively optimize the unrolled block to clean it up
                        optimizeBlock(unrolledBlock);
                        return unrolledBlock;
                    }
                }
            }
        }
        optimizeBlock(loop->body);
        return loop;
    }
    else if (auto par = dynamic_cast<ParallelStmt *>(stmt))
    {
        optimizeBlock(par->body);
        return par;
    }
    else if (auto func = dynamic_cast<FuncDecl *>(stmt))
    {
        optimizeBlock(func->body);
        return func;
    }

    return stmt;
}

Expression *Optimizer::optimizeExpression(Expression *expr)
{
    if (!expr)
        return nullptr;

    if (auto id = dynamic_cast<Identifier *>(expr))
    {
        auto it = constantTable.find(id->name);
        if (it != constantTable.end())
        {
            return cloneLiteral(it->second);
        }
        return expr;
    }

    if (auto bin = dynamic_cast<BinaryExpr *>(expr))
    {
        bin->left = optimizeExpression(bin->left);
        bin->right = optimizeExpression(bin->right);
        if (isConstant(bin->left) && isConstant(bin->right))
        {
            return foldBinary(bin, bin->left, bin->right);
        }
    }
    else if (auto rng = dynamic_cast<RangeExpr *>(expr))
    {
        rng->start = optimizeExpression(rng->start);
        rng->end = optimizeExpression(rng->end);
    }
    else if (auto arr = dynamic_cast<ArrayLiteral *>(expr))
    {
        for (size_t i = 0; i < arr->elements.size(); ++i)
        {
            arr->elements[i] = optimizeExpression(arr->elements[i]);
        }
    }
    else if (auto call = dynamic_cast<MethodCallExpr *>(expr))
    {
        call->object = optimizeExpression(call->object);
        for (size_t i = 0; i < call->args.size(); ++i)
        {
            call->args[i] = optimizeExpression(call->args[i]);
        }
    }
    else if (auto idx = dynamic_cast<IndexExpr *>(expr))
    {
        idx->array = optimizeExpression(idx->array);
        idx->index = optimizeExpression(idx->index);
    }
    else if (auto unary = dynamic_cast<UnaryExpr *>(expr))
    {
        unary->operand = optimizeExpression(unary->operand);
    }
    else if (auto call = dynamic_cast<CallExpr *>(expr))
    {
        for (size_t i = 0; i < call->args.size(); ++i)
        {
            call->args[i] = optimizeExpression(call->args[i]);
        }
    }

    return expr;
}

bool Optimizer::isConstant(Expression *expr)
{
    if (!expr)
        return false;
    return (dynamic_cast<IntLiteral *>(expr) ||
            dynamic_cast<FloatLiteral *>(expr) ||
            dynamic_cast<BoolLiteral *>(expr));
}

Expression *Optimizer::cloneLiteral(Expression *lit)
{
    if (auto i = dynamic_cast<IntLiteral *>(lit))
        return (Expression *)(new IntLiteral(i->value))->loc(lit->line, lit->col);
    if (auto f = dynamic_cast<FloatLiteral *>(lit))
        return (Expression *)(new FloatLiteral(f->value))->loc(lit->line, lit->col);
    if (auto b = dynamic_cast<BoolLiteral *>(lit))
        return (Expression *)(new BoolLiteral(b->value))->loc(lit->line, lit->col);
    return nullptr;
}

Expression *Optimizer::foldBinary(BinaryExpr *expr, Expression *left, Expression *right)
{
    int line = expr->line;
    int col = expr->col;

    if (auto l = dynamic_cast<BoolLiteral *>(left))
    {
        if (auto r = dynamic_cast<BoolLiteral *>(right))
        {
            switch (expr->op)
            {
            case OpType::AND:
                return (Expression *)(new BoolLiteral(l->value && r->value))->loc(line, col);
            case OpType::OR:
                return (Expression *)(new BoolLiteral(l->value || r->value))->loc(line, col);
            case OpType::EQ:
                return (Expression *)(new BoolLiteral(l->value == r->value))->loc(line, col);
            case OpType::NEQ:
                return (Expression *)(new BoolLiteral(l->value != r->value))->loc(line, col);
            default:
                return expr;
            }
        }
    }
    if (auto l = dynamic_cast<IntLiteral *>(left))
    {
        if (auto r = dynamic_cast<IntLiteral *>(right))
        {
            int result = 0;
            switch (expr->op)
            {
            case OpType::PLUS:
                return (Expression *)(new IntLiteral(l->value + r->value))->loc(line, col);
            case OpType::MINUS:
                return (Expression *)(new IntLiteral(l->value - r->value))->loc(line, col);
            case OpType::MUL:
                return (Expression *)(new IntLiteral(l->value * r->value))->loc(line, col);
            case OpType::DIV:
                return (Expression *)(new IntLiteral((r->value != 0) ? l->value / r->value : 0))->loc(line, col);
            case OpType::POWER:
                return (Expression *)(new IntLiteral(std::pow(l->value, r->value)))->loc(line, col);
            case OpType::LT:
                return (Expression *)(new BoolLiteral(l->value < r->value))->loc(line, col);
            case OpType::GT:
                return (Expression *)(new BoolLiteral(l->value > r->value))->loc(line, col);
            case OpType::LTE:
                return (Expression *)(new BoolLiteral(l->value <= r->value))->loc(line, col);
            case OpType::GTE:
                return (Expression *)(new BoolLiteral(l->value >= r->value))->loc(line, col);
            case OpType::EQ:
                return (Expression *)(new BoolLiteral(l->value == r->value))->loc(line, col);
            case OpType::NEQ:
                return (Expression *)(new BoolLiteral(l->value != r->value))->loc(line, col);
            case OpType::LSHIFT:
                return (Expression *)(new IntLiteral(l->value << r->value))->loc(line, col);
            case OpType::RSHIFT:
                return (Expression *)(new IntLiteral(l->value >> r->value))->loc(line, col);
            case OpType::AND:
                return (Expression *)(new BoolLiteral((bool)l->value && (bool)r->value))->loc(line, col);
            case OpType::OR:
                return (Expression *)(new BoolLiteral((bool)l->value || (bool)r->value))->loc(line, col);
            default:
                return expr;
            }
        }
        else if (auto rF = dynamic_cast<FloatLiteral *>(right))
        {
            double valL = (double)l->value;
            double valR = rF->value;
            switch (expr->op)
            {
            case OpType::PLUS:
                return (Expression *)(new FloatLiteral(valL + valR))->loc(line, col);
            case OpType::MINUS:
                return (Expression *)(new FloatLiteral(valL - valR))->loc(line, col);
            case OpType::MUL:
                return (Expression *)(new FloatLiteral(valL * valR))->loc(line, col);
            case OpType::DIV:
                return (Expression *)(new FloatLiteral(valL / valR))->loc(line, col);
            case OpType::POWER:
                return (Expression *)(new FloatLiteral(std::pow(valL, valR)))->loc(line, col);
            default:
                return expr;
            }
        }
    }
    else if (auto l = dynamic_cast<FloatLiteral *>(left))
    {
        double valL = l->value;
        double valR = 0.0;

        if (auto rInt = dynamic_cast<IntLiteral *>(right))
            valR = (double)rInt->value;
        else if (auto rF = dynamic_cast<FloatLiteral *>(right))
            valR = rF->value;
        else
            return expr;

        switch (expr->op)
        {
        case OpType::PLUS:
            return (Expression *)(new FloatLiteral(valL + valR))->loc(line, col);
        case OpType::MINUS:
            return (Expression *)(new FloatLiteral(valL - valR))->loc(line, col);
        case OpType::MUL:
            return (Expression *)(new FloatLiteral(valL * valR))->loc(line, col);
        case OpType::DIV:
            return (Expression *)(new FloatLiteral(valL / valR))->loc(line, col);
        case OpType::POWER:
            return (Expression *)(new FloatLiteral(std::pow(valL, valR)))->loc(line, col);
        default:
            return expr;
        }
    }

    return expr;
}

void Optimizer::optimizePeephole(std::vector<Statement *> &stmts)
{
    std::vector<Statement *> output;

    for (Statement *stmt : stmts)
    {
        bool consumed = false;

        if (auto exprStmt = dynamic_cast<ExprStmt *>(stmt))
        {
            if (auto call = dynamic_cast<MethodCallExpr *>(exprStmt->expr))
            {

                // Check against the LAST statement added to output
                if (!output.empty())
                {
                    if (auto prevStmt = dynamic_cast<ExprStmt *>(output.back()))
                    {
                        if (auto prevCall = dynamic_cast<MethodCallExpr *>(prevStmt->expr))
                        {

                            if (areExpressionsEqual(call->object, prevCall->object))
                            {

                                if (call->method == prevCall->method && isSelfInverse(call->method))
                                {
                                    bool argsMatch = true;
                                    if (call->args.size() != prevCall->args.size())
                                        argsMatch = false;
                                    else
                                    {
                                        for (size_t k = 0; k < call->args.size(); k++)
                                        {
                                            if (!areExpressionsEqual(call->args[k], prevCall->args[k]))
                                            {
                                                argsMatch = false;
                                                break;
                                            }
                                        }
                                    }

                                    if (argsMatch)
                                    {
                                        output.pop_back(); // Remove previous
                                        consumed = true;   // Skip current
                                    }
                                }

                                else if (call->method == prevCall->method && isRotation(call->method))
                                {
                                    if (call->args.size() == 1 && prevCall->args.size() == 1)
                                    {
                                        Expression *angle1 = prevCall->args[0];
                                        Expression *angle2 = call->args[0];

                                        BinaryExpr *newAngle = new BinaryExpr(angle1->clone(), OpType::PLUS, angle2->clone());
                                        prevCall->args[0] = optimizeExpression(newAngle);

                                        consumed = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (!consumed)
        {
            output.push_back(stmt);
        }
    }

    stmts = output;
}

bool Optimizer::isSelfInverse(const std::string &name)
{
    return (name == "h" || name == "x" || name == "y" || name == "z" ||
            name == "cnot" || name == "cx" || name == "cz");
}

bool Optimizer::isRotation(const std::string &name)
{
    return (name == "rx" || name == "ry" || name == "rz" || name == "p" || name == "rzz");
}

bool Optimizer::areExpressionsEqual(Expression *a, Expression *b)
{
    if (a == b)
        return true;
    if (!a || !b)
        return false;

    if (auto idA = dynamic_cast<Identifier *>(a))
    {
        if (auto idB = dynamic_cast<Identifier *>(b))
            return idA->name == idB->name;
    }
    else if (auto iA = dynamic_cast<IntLiteral *>(a))
    {
        if (auto iB = dynamic_cast<IntLiteral *>(b))
            return iA->value == iB->value;
    }
    else if (auto fA = dynamic_cast<FloatLiteral *>(a))
    {
        if (auto fB = dynamic_cast<FloatLiteral *>(b))
            return fA->value == fB->value;
    }
    else if (auto idxA = dynamic_cast<IndexExpr *>(a))
    {
        if (auto idxB = dynamic_cast<IndexExpr *>(b))
        {
            return areExpressionsEqual(idxA->array, idxB->array) &&
                   areExpressionsEqual(idxA->index, idxB->index);
        }
    }
    return false;
}