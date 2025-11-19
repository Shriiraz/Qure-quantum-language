#pragma once

#include "ast.hpp"
#include <ostream>
#include <string>

class CodeGenerator {
public:
    // Write to file or stdout (std::cout)
    CodeGenerator(std::ostream& os) : out(os), indentLevel(0) {}
    void generate(Program* root);

private:
    std::ostream& out;
    int indentLevel;

    void emitIndent();
    
    // Visitors
    void visitStatement(Statement* stmt);
    void visitBlock(Block* block);
    void visitExpression(Expression* expr);
    
    // Helpers
    std::string getOperator(OpType op);
};