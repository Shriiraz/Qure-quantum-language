#pragma once

#include "ast.hpp"
#include <cmath>
#include <map>
#include <string>

class Optimizer {
public:
    Optimizer();
    void optimize(Program* root);

    // Helper to check if two expressions look exactly the same
    // e.g. q[0] == q[0], but q[0] != q[1]
    bool areExpressionsEqual(Expression* a, Expression* b);
    
    // Check if a method name is self-inverse (h, x, z, etc.)
    bool isSelfInverse(const std::string& name);

    bool isRotation(const std::string& name);

private:
    // Symbol table for constants (Name -> Value Node)
    // We store the ASTNode* so we can clone it when replacing Identifiers
    std::map<std::string, Expression*> constantTable;

    void optimizeBlock(Block* block);
    Statement* optimizeStatement(Statement* stmt);
    
    Expression* optimizeExpression(Expression* expr);
    Expression* foldBinary(BinaryExpr* expr, Expression* left, Expression* right);
    
    bool isConstant(Expression* expr);
    
    // Helper to clone a literal node (needed for propagation)
    Expression* cloneLiteral(Expression* lit);

    // Gate Cancellation Logic
    void optimizePeephole(std::vector<Statement*>& statements);
};