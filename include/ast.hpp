#pragma once

#include <iostream>
#include <vector>
#include <string>

// Enum Definitions
enum class OpType
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    POWER,
    EQ,
    NEQ,
    LT,
    LTE,
    GT,
    GTE,
    AND,
    OR,
    NOT,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    LSHIFT,
    RSHIFT,
    BIT_NOT,
    ASSIGN,
    PLUS_ASSIGN,
    MINUS_ASSIGN
};

enum class DataType
{
    VOID,
    INT,
    FLOAT,
    ANGLE,
    BOOL,
    STRING,
    COMPLEX,
    QUBIT,
    BIT,
    MATRIX,
    AUTO
};

// Base Node

class ASTNode
{
public:
    int line = 0;
    int col = 0;

    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;

    virtual ASTNode *clone() const = 0;

    // Helper to set location and return this as ASTNode*
    ASTNode *loc(int l, int c)
    {
        line = l;
        col = c;
        return this;
    }
};

inline void printIndent(int indent)
{
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
}

class Expression : public ASTNode
{
public:
    virtual Expression *clone() const override = 0;
};

class Identifier : public Expression
{
public:
    std::string name;
    Identifier(const std::string &n) : name(n) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Identifier: " << name << "\n";
    }
    Expression *clone() const override { return (Expression *)(new Identifier(name))->loc(line, col); }
};

class IntLiteral : public Expression
{
public:
    int value;
    IntLiteral(int v) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Int: " << value << "\n";
    }
    Expression *clone() const override { return (Expression *)(new IntLiteral(value))->loc(line, col); }
};

class FloatLiteral : public Expression
{
public:
    double value;
    FloatLiteral(double v) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Float: " << value << "\n";
    }
    Expression *clone() const override { return (Expression *)(new FloatLiteral(value))->loc(line, col); }
};

class BoolLiteral : public Expression
{
public:
    bool value;
    BoolLiteral(bool v) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Bool: " << (value ? "true" : "false") << "\n";
    }
    Expression *clone() const override { return (Expression *)(new BoolLiteral(value))->loc(line, col); }
};

class StringLiteral : public Expression
{
public:
    std::string value;
    StringLiteral(const std::string &v) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "String: \"" << value << "\"\n";
    }
    Expression *clone() const override { return (Expression *)(new StringLiteral(value))->loc(line, col); }
};

class ImaginaryLiteral : public Expression
{
public:
    double value;
    ImaginaryLiteral(double v) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Imaginary: " << value << "i\n";
    }
    Expression *clone() const override { return (Expression *)(new ImaginaryLiteral(value))->loc(line, col); }
};

class ArrayLiteral : public Expression
{
public:
    std::vector<Expression *> elements;
    ArrayLiteral(std::vector<Expression *> els) : elements(els) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Array/Matrix Literal [" << elements.size() << "]\n";
        for (auto e : elements)
            e->print(indent + 1);
    }
    Expression *clone() const override
    {
        std::vector<Expression *> newEls;
        for (auto e : elements)
            newEls.push_back(e->clone());
        return (Expression *)(new ArrayLiteral(newEls))->loc(line, col);
    }
};

class BinaryExpr : public Expression
{
public:
    Expression *left;
    OpType op;
    Expression *right;
    BinaryExpr(Expression *l, OpType o, Expression *r) : left(l), op(o), right(r) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Binary Op\n";
        left->print(indent + 1);
        right->print(indent + 1);
    }
    Expression *clone() const override
    {
        return (Expression *)(new BinaryExpr(left->clone(), op, right->clone()))->loc(line, col);
    }
};

class UnaryExpr : public Expression
{
public:
    OpType op;
    Expression *operand;
    UnaryExpr(OpType o, Expression *e) : op(o), operand(e) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Unary Op\n";
        operand->print(indent + 1);
    }
    Expression *clone() const override
    {
        return (Expression *)(new UnaryExpr(op, operand->clone()))->loc(line, col);
    }
};

class IndexExpr : public Expression
{
public:
    Expression *array;
    Expression *index;
    IndexExpr(Expression *a, Expression *i) : array(a), index(i) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Index Access\n";
        array->print(indent + 1);
        index->print(indent + 1);
    }
    Expression *clone() const override
    {
        return (Expression *)(new IndexExpr(array->clone(), index->clone()))->loc(line, col);
    }
};

class RangeExpr : public Expression
{
public:
    Expression *start;
    Expression *end;
    RangeExpr(Expression *s, Expression *e) : start(s), end(e) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Range\n";
        start->print(indent + 1);
        end->print(indent + 1);
    }
    Expression *clone() const override
    {
        return (Expression *)(new RangeExpr(start->clone(), end->clone()))->loc(line, col);
    }
};

class CallExpr : public Expression
{
public:
    std::string callee;
    std::vector<Expression *> args;
    CallExpr(const std::string &name, std::vector<Expression *> a) : callee(name), args(a) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Call: " << callee << "\n";
        for (auto a : args)
            a->print(indent + 1);
    }
    Expression *clone() const override
    {
        std::vector<Expression *> newArgs;
        for (auto a : args)
            newArgs.push_back(a->clone());
        return (Expression *)(new CallExpr(callee, newArgs))->loc(line, col);
    }
};

class MethodCallExpr : public Expression
{
public:
    Expression *object;
    std::string method;
    std::vector<Expression *> args;
    MethodCallExpr(Expression *obj, const std::string &m, std::vector<Expression *> a)
        : object(obj), method(m), args(a) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Method: ." << method << "()\n";
        object->print(indent + 1);
        for (auto a : args)
            a->print(indent + 1);
    }
    Expression *clone() const override
    {
        std::vector<Expression *> newArgs;
        for (auto a : args)
            newArgs.push_back(a->clone());
        return (Expression *)(new MethodCallExpr(object->clone(), method, newArgs))->loc(line, col);
    }
};

class Statement : public ASTNode
{
public:
    virtual Statement *clone() const override = 0;
};

class Block : public Statement
{
public:
    std::vector<Statement *> statements;
    Block() {}
    void add(Statement *s) { statements.push_back(s); }
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Block\n";
        for (auto s : statements)
            s->print(indent + 1);
    }
    Statement *clone() const override
    {
        Block *b = new Block();
        for (auto s : statements)
            b->add(s->clone());
        return (Statement *)b->loc(line, col);
    }
};

class ExprStmt : public Statement
{
public:
    Expression *expr;
    ExprStmt(Expression *e) : expr(e) {}
    void print(int indent) const override
    {
        expr->print(indent);
    }
    Statement *clone() const override { return (Statement *)(new ExprStmt(expr->clone()))->loc(line, col); }
};

class IfStmt : public Statement
{
public:
    Expression *condition;
    Block *thenBlock;
    Statement *elseBlock;
    IfStmt(Expression *c, Block *t, Statement *e = nullptr)
        : condition(c), thenBlock(t), elseBlock(e) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "If Statement\n";
        condition->print(indent + 1);
        thenBlock->print(indent + 1);
        if (elseBlock)
            elseBlock->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new IfStmt(condition->clone(), (Block *)thenBlock->clone(), elseBlock ? elseBlock->clone() : nullptr))->loc(line, col);
    }
};

class WhileStmt : public Statement
{
public:
    Expression *condition;
    Block *body;
    WhileStmt(Expression *c, Block *b) : condition(c), body(b) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "While Loop\n";
        condition->print(indent + 1);
        body->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new WhileStmt(condition->clone(), (Block *)body->clone()))->loc(line, col);
    }
};

class ForStmt : public Statement
{
public:
    std::string iterator;
    Expression *iterable;
    Block *body;
    ForStmt(const std::string &iter, Expression *range, Block *b)
        : iterator(iter), iterable(range), body(b) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "For Loop (" << iterator << ")\n";
        iterable->print(indent + 1);
        body->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new ForStmt(iterator, iterable->clone(), (Block *)body->clone()))->loc(line, col);
    }
};

class ReturnStmt : public Statement
{
public:
    Expression *value;
    ReturnStmt(Expression *v = nullptr) : value(v) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Return\n";
        if (value)
            value->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new ReturnStmt(value ? value->clone() : nullptr))->loc(line, col);
    }
};

class ParallelStmt : public Statement
{
public:
    std::string mode;
    Block *body;
    ParallelStmt(const std::string &m, Block *b) : mode(m), body(b) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Parallel (" << mode << ")\n";
        body->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new ParallelStmt(mode, (Block *)body->clone()))->loc(line, col);
    }
};

class DelayStmt : public Statement
{
public:
    Expression *duration;
    Expression *target;
    DelayStmt(Expression *d, Expression *t) : duration(d), target(t) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Delay\n";
        duration->print(indent + 1);
        target->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new DelayStmt(duration->clone(), target->clone()))->loc(line, col);
    }
};

class BarrierStmt : public Statement
{
public:
    std::vector<Expression *> targets;
    BarrierStmt(std::vector<Expression *> t) : targets(t) {}
    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << "Barrier\n";
    }
    Statement *clone() const override
    {
        return (Statement *)(new BarrierStmt(targets))->loc(line, col);
    }
};

struct TypeSpecifier
{
    DataType baseType;
    bool isArray;
    std::vector<int> dimensions;
};

class VarDecl : public Statement
{
public:
    std::string name;
    TypeSpecifier type;
    Expression *initializer;
    Expression *arraySizeExpr;
    bool isConst;

    VarDecl(const std::string &n, TypeSpecifier t, Expression *init, bool c = false, Expression *sizeExpr = nullptr)
        : name(n), type(t), initializer(init), isConst(c), arraySizeExpr(sizeExpr) {}

    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << (isConst ? "Const " : "Var ") << name;
        if (arraySizeExpr)
        {
            std::cout << "[Expr]";
        }
        std::cout << "\n";
        if (initializer)
            initializer->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new VarDecl(name, type, initializer ? initializer->clone() : nullptr, isConst, arraySizeExpr ? arraySizeExpr->clone() : nullptr))->loc(line, col);
    }
};

struct Parameter
{
    std::string name;
    TypeSpecifier type;
};

class FuncDecl : public Statement
{
public:
    std::string name;
    std::vector<Parameter> params;
    TypeSpecifier returnType;
    Block *body;
    bool isQuantum;

    FuncDecl(const std::string &n, const std::vector<Parameter> &p, Block *b, bool q)
        : name(n), params(p), body(b), isQuantum(q) {}

    void print(int indent) const override
    {
        printIndent(indent);
        std::cout << (isQuantum ? "Circuit: " : "Function: ") << name << "(";
        for (size_t i = 0; i < params.size(); ++i)
        {
            std::cout << params[i].name;
            if (i < params.size() - 1)
                std::cout << ", ";
        }
        std::cout << ")\n";
        body->print(indent + 1);
    }
    Statement *clone() const override
    {
        return (Statement *)(new FuncDecl(name, params, (Block *)body->clone(), isQuantum))->loc(line, col);
    }
};

class Program : public ASTNode
{
public:
    std::vector<ASTNode *> declarations;
    void add(ASTNode *d) { declarations.push_back(d); }
    void print(int indent = 0) const override
    {
        std::cout << "Program AST:\n";
        for (auto d : declarations)
            d->print(indent + 1);
    }
    ASTNode *clone() const override { return nullptr; }
};