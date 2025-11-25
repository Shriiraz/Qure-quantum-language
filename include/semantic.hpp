#pragma once

#include "ast.hpp"
#include "symbol_table.hpp"

class SemanticAnalyzer {
private:
    SymbolTable symTable;
    bool hasError;

    void error(ASTNode* node, const std::string& msg);
    
    // Core traversal methods
    void checkProgram(Program* node);
    void checkStatement(Statement* stmt);
    void checkBlock(Block* block);
    void checkVarDecl(VarDecl* decl);
    void checkFuncDecl(FuncDecl* decl);

    DataType checkExpression(Expression* expr);
    
    DataType checkBinary(BinaryExpr* expr);
    DataType checkMethodCall(MethodCallExpr* expr);
    DataType checkIdentifier(Identifier* expr);
    DataType checkCall(CallExpr* expr);
    
    // Helpers
    bool isQuantumType(DataType t);
    bool isNumber(DataType t);
    std::string typeToString(DataType t);

public:
    SemanticAnalyzer();
    bool analyze(Program* root);
};