%{
#include <iostream>
#include <vector>
#include <string>
#include "../include/ast.hpp"

typedef void* yyscan_t;
extern int yylex(union YYSTYPE * yylval_param, struct YYLTYPE * yylloc_param, yyscan_t scanner);
void yyerror(const YYLTYPE* loc, yyscan_t scanner, Program** root, const char *s);
%}

%code requires {
    #include "../include/ast.hpp"
    typedef void* yyscan_t; 
}

%define api.pure full
%locations
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { Program** root }

%union {
    int ival;
    double fval;
    std::string* sval;
    ASTNode* node;
    Expression* expr;
    Statement* stmt;
    Block* block;
    std::vector<Expression*>* expr_list;
    std::vector<Statement*>* stmt_list;
    int type_enum;
    
    /* NEW FIELDS */
    Parameter* parameter;
    std::vector<Parameter>* param_list;
}

%token <ival> INT_LIT BOOL_LIT
%token <fval> FLOAT_LIT IMAG_LIT
%token <sval> STRING_LIT ID TIME_LIT

%token KW_IMPORT KW_CONST KW_VAR KW_LET
%token KW_INT KW_FLOAT KW_ANGLE KW_BOOL KW_STRING KW_COMPLEX KW_MATRIX
%token KW_QUBIT KW_BIT
%token KW_FUNC KW_CIRCUIT KW_RETURN
%token KW_ALIAS
%token KW_IF KW_ELSE KW_WHILE KW_FOR KW_FOREACH KW_IN
%token KW_PARALLEL KW_STRETCH KW_BOX KW_DELAY KW_BARRIER

%token ARROW RANGE DOT COMMA SEMICOLON COLON AT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

/* Precedence */
%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE
%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQ NEQ
%left LT GT LTE GTE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR SLASH PERCENT
%right POWER
%right NOT BIT_NOT UMINUS

%type <stmt_list> stmt_list
%type <node> declaration
%type <parameter> param
%type <param_list> param_list
%type <stmt> statement var_decl func_decl circuit_decl
%type <block> block
%type <expr> expression assignment range_expr logical_or logical_and equality relational shift_expr
%type <expr> additive multiplicative bitwise unary primary postfix
%type <expr_list> argument_list elements
%type <sval> import_path
%type <type_enum> primitive_type

%%

program:
    /* empty */ { *root = new Program(); }
    | program declaration { (*root)->add($2); }
    ;

declaration:
    func_decl { $$ = $1; }
    | circuit_decl { $$ = $1; }
    | statement { $$ = $1; }
    | KW_IMPORT import_path SEMICOLON { 
        Expression* s = new StringLiteral(*$2); s->loc(@2.first_line, @2.first_column);
        $$ = (new ExprStmt(s))->loc(@1.first_line, @1.first_column);
    }
    ;

import_path:
    ID { $$ = $1; }
    | import_path DOT ID { 
        $$ = new std::string(*$1 + "." + *$3);
        delete $1; delete $3; 
    }
    ;

block:
    LBRACE RBRACE { 
        $$ = (Block*)(new Block())->loc(@1.first_line, @1.first_column); 
    }
    | LBRACE stmt_list RBRACE {
        Block* b = new Block();
        b->statements = *$2;
        b->loc(@1.first_line, @1.first_column);
        delete $2;
        $$ = b;
    }
    ;

stmt_list:
    statement { 
        $$ = new std::vector<Statement*>();
        $$->push_back($1); 
    }
    | stmt_list statement {
        $1->push_back($2);
        $$ = $1;
    }
    ;

statement:
    block { $$ = $1; }
    | var_decl { $$ = $1; }
    | expression SEMICOLON { 
        $$ = (Statement*)(new ExprStmt($1))->loc(@1.first_line, @1.first_column); 
    }
    | SEMICOLON { 
        $$ = (Statement*)(new Block())->loc(@1.first_line, @1.first_column); 
    }
    | KW_RETURN expression SEMICOLON { 
        $$ = (Statement*)(new ReturnStmt($2))->loc(@1.first_line, @1.first_column); 
    }
    | KW_RETURN SEMICOLON { 
        $$ = (Statement*)(new ReturnStmt(nullptr))->loc(@1.first_line, @1.first_column); 
    }
    
    | KW_IF LPAREN expression RPAREN block %prec LOWER_THAN_ELSE { 
        $$ = (Statement*)(new IfStmt($3, $5))->loc(@1.first_line, @1.first_column); 
    }
    | KW_IF LPAREN expression RPAREN block KW_ELSE statement { 
        $$ = (Statement*)(new IfStmt($3, $5, $7))->loc(@1.first_line, @1.first_column); 
    }
    
    | KW_WHILE LPAREN expression RPAREN block {
        $$ = (Statement*)(new WhileStmt($3, $5))->loc(@1.first_line, @1.first_column);
    }
    | KW_FOR ID KW_IN expression block {
        $$ = (Statement*)(new ForStmt(*$2, $4, $5))->loc(@1.first_line, @1.first_column);
    }
    | KW_FOREACH ID KW_IN expression block {
        $$ = (Statement*)(new ForStmt(*$2, $4, $5))->loc(@1.first_line, @1.first_column);
    }
    
    | KW_PARALLEL block {
        $$ = (Statement*)(new ParallelStmt("default", $2))->loc(@1.first_line, @1.first_column);
    }
    | KW_PARALLEL LPAREN ID RPAREN block {
        $$ = (Statement*)(new ParallelStmt(*$3, $5))->loc(@1.first_line, @1.first_column);
    }
    | KW_PARALLEL LPAREN KW_STRETCH RPAREN block {
        $$ = (Statement*)(new ParallelStmt("stretch", $5))->loc(@1.first_line, @1.first_column);
    }
    | KW_PARALLEL LPAREN KW_BOX RPAREN block {
        $$ = (Statement*)(new ParallelStmt("box", $5))->loc(@1.first_line, @1.first_column);
    }

    | KW_DELAY expression AT expression SEMICOLON {
        $$ = (Statement*)(new DelayStmt($2, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_BARRIER SEMICOLON {
        $$ = (Statement*)(new BarrierStmt({}))->loc(@1.first_line, @1.first_column);
    }
    ;

var_decl:
    /* --- INT --- */
    KW_INT ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::INT, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_INT ID LBRACKET expression RBRACKET ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::INT, true, {} }; 
        $$ = (Statement*)(new VarDecl(*$2, t, $7, false, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_INT ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::INT, true, {} }; 
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }
    
    /* --- FLOAT --- */
    | KW_FLOAT ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::FLOAT, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_FLOAT ID LBRACKET expression RBRACKET ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::FLOAT, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $7, false, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_FLOAT ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::FLOAT, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }

    /* --- COMPLEX --- */
    | KW_COMPLEX ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::COMPLEX, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_COMPLEX ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::COMPLEX, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }
    
    /* --- BOOL --- */
    | KW_BOOL ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::BOOL, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_BOOL ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::BOOL, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }
    
    /* --- STRING --- */
    | KW_STRING ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::STRING, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_STRING ID LBRACKET expression RBRACKET SEMICOLON { 
        TypeSpecifier t = { DataType::STRING, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }

    /* --- ANGLE --- */
    | KW_ANGLE ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::ANGLE, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_ANGLE ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::ANGLE, true, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }

    /* --- INFERENCE (VAR/LET/ALIAS) --- */
    | KW_VAR ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_VAR ID SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr))->loc(@1.first_line, @1.first_column);
    }

    | KW_CONST ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4, true))->loc(@1.first_line, @1.first_column);
    }
    | KW_CONST ID SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, true))->loc(@1.first_line, @1.first_column);
    }

    | KW_ALIAS ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_ALIAS ID SEMICOLON {
        TypeSpecifier t = { DataType::AUTO, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr))->loc(@1.first_line, @1.first_column);
    }

    /* --- QUANTUM --- */
    | KW_QUBIT ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::QUBIT, true, {1} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }
    | KW_BIT ID LBRACKET expression RBRACKET SEMICOLON {
        TypeSpecifier t = { DataType::BIT, true, {1} };
        $$ = (Statement*)(new VarDecl(*$2, t, nullptr, false, $4))->loc(@1.first_line, @1.first_column);
    }
    
    /* --- MATRIX --- */
    | KW_MATRIX ID ASSIGN expression SEMICOLON {
        TypeSpecifier t = { DataType::MATRIX, false, {} };
        $$ = (Statement*)(new VarDecl(*$2, t, $4))->loc(@1.first_line, @1.first_column);
    }
    ;

primitive_type:
    KW_INT     { $$ = (int)DataType::INT; }
    | KW_FLOAT { $$ = (int)DataType::FLOAT; }
    | KW_ANGLE { $$ = (int)DataType::ANGLE; }
    | KW_BOOL  { $$ = (int)DataType::BOOL; }
    | KW_QUBIT { $$ = (int)DataType::QUBIT; }
    | KW_BIT   { $$ = (int)DataType::BIT; }
    ;

param:
    ID COLON primitive_type {
        TypeSpecifier t = { (DataType)$3, false, {} };
        $$ = new Parameter{*$1, t};
        delete $1;
    }
    | ID COLON primitive_type LBRACKET RBRACKET {
        TypeSpecifier t = { (DataType)$3, true, {} };
        $$ = new Parameter{*$1, t};
        delete $1;
    }
    ;

param_list:
    /* empty */ { 
        $$ = new std::vector<Parameter>(); 
    }
    | param {
        $$ = new std::vector<Parameter>();
        $$->push_back(*$1);
        delete $1;
    }
    | param_list COMMA param {
        $1->push_back(*$3);
        delete $3;
        $$ = $1;
    }
    ;

func_decl:
    KW_FUNC ID LPAREN param_list RPAREN block {
        $$ = (Statement*)(new FuncDecl(*$2, *$4, $6, false))->loc(@1.first_line, @1.first_column);
        delete $2; delete $4;
    }
    ;

circuit_decl:
    KW_CIRCUIT ID LPAREN param_list RPAREN block {
        $$ = (Statement*)(new FuncDecl(*$2, *$4, $6, true))->loc(@1.first_line, @1.first_column);
        delete $2; delete $4;
    }
    ;

expression: assignment ;

assignment:
    postfix ASSIGN expression { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::ASSIGN, $3))->loc(@2.first_line, @2.first_column); 
    }
    | postfix PLUS_ASSIGN expression { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::PLUS_ASSIGN, $3))->loc(@2.first_line, @2.first_column); 
    }
    | postfix MINUS_ASSIGN expression { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::MINUS_ASSIGN, $3))->loc(@2.first_line, @2.first_column); 
    }
    | range_expr
    ;

range_expr:
    logical_or RANGE logical_or { 
        $$ = (Expression*)(new RangeExpr($1, $3))->loc(@2.first_line, @2.first_column); 
    }
    | logical_or
    ;

logical_or:
    logical_or OR logical_and { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::OR, $3))->loc(@2.first_line, @2.first_column); 
    }
    | logical_and
    ;

logical_and:
    logical_and AND bitwise { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::AND, $3))->loc(@2.first_line, @2.first_column); 
    }
    | bitwise
    ;

bitwise:
    bitwise BIT_OR equality { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::BIT_OR, $3))->loc(@2.first_line, @2.first_column); 
    }
    | bitwise BIT_XOR equality { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::BIT_XOR, $3))->loc(@2.first_line, @2.first_column); 
    }
    | bitwise BIT_AND equality { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::BIT_AND, $3))->loc(@2.first_line, @2.first_column); 
    }
    | equality
    ;

equality:
    equality EQ relational { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::EQ, $3))->loc(@2.first_line, @2.first_column); 
    }
    | equality NEQ relational { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::NEQ, $3))->loc(@2.first_line, @2.first_column); 
    }
    | relational
    ;

relational:
    relational LT shift_expr { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::LT, $3))->loc(@2.first_line, @2.first_column); 
    }
    | relational GT shift_expr { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::GT, $3))->loc(@2.first_line, @2.first_column); 
    }
    | relational LTE shift_expr { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::LTE, $3))->loc(@2.first_line, @2.first_column); 
    }
    | relational GTE shift_expr { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::GTE, $3))->loc(@2.first_line, @2.first_column); 
    }
    | shift_expr
    ;

shift_expr:
    shift_expr LSHIFT additive { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::LSHIFT, $3))->loc(@2.first_line, @2.first_column); 
    }
    | shift_expr RSHIFT additive { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::RSHIFT, $3))->loc(@2.first_line, @2.first_column); 
    }
    | additive
    ;

additive:
    additive PLUS multiplicative { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::PLUS, $3))->loc(@2.first_line, @2.first_column); 
    }
    | additive MINUS multiplicative { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::MINUS, $3))->loc(@2.first_line, @2.first_column); 
    }
    | multiplicative
    ;

multiplicative:
    multiplicative STAR unary { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::MUL, $3))->loc(@2.first_line, @2.first_column); 
    }
    | multiplicative SLASH unary { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::DIV, $3))->loc(@2.first_line, @2.first_column); 
    }
    | multiplicative PERCENT unary { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::MOD, $3))->loc(@2.first_line, @2.first_column); 
    }
    | multiplicative POWER unary { 
        $$ = (Expression*)(new BinaryExpr($1, OpType::POWER, $3))->loc(@2.first_line, @2.first_column); 
    }
    | unary
    ;

unary:
    NOT unary { 
        $$ = (Expression*)(new UnaryExpr(OpType::NOT, $2))->loc(@1.first_line, @1.first_column); 
    }
    | MINUS unary %prec UMINUS { 
        $$ = (Expression*)(new UnaryExpr(OpType::MINUS, $2))->loc(@1.first_line, @1.first_column); 
    }
    | postfix
    ;

postfix:
    primary
    | postfix DOT ID LPAREN argument_list RPAREN {
        $$ = (Expression*)(new MethodCallExpr($1, *$3, *$5))->loc(@2.first_line, @2.first_column);
        delete $3; delete $5;
    }
    | postfix DOT ID LPAREN RPAREN {
        $$ = (Expression*)(new MethodCallExpr($1, *$3, {}))->loc(@2.first_line, @2.first_column);
        delete $3;
    }
    | postfix LBRACKET expression RBRACKET {
        $$ = (Expression*)(new IndexExpr($1, $3))->loc(@2.first_line, @2.first_column);
    }
    
    | postfix LPAREN argument_list RPAREN {
        /* Check if the left side is an Identifier */
        if (auto id = dynamic_cast<Identifier*>($1)) {
            $$ = (Expression*)(new CallExpr(id->name, *$3))->loc(@2.first_line, @2.first_column);
            /* We extracted the name, so we can delete the ID node */
            delete id;
        } else {
            /* Error case: Trying to call (1+2)(args) or similar */
            /* For resilience, create a call to "unknown" or handle error reporting here */
            $$ = $1; // Fallback (or trigger yyerror)
            std::cerr << "Syntax Error: Call must be on an identifier." << std::endl;
        }
        delete $3; 
    }
    | postfix LPAREN RPAREN {
        if (auto id = dynamic_cast<Identifier*>($1)) {
            $$ = (Expression*)(new CallExpr(id->name, {}))->loc(@2.first_line, @2.first_column);
            delete id;
        } else {
            $$ = $1; 
            std::cerr << "Syntax Error: Call must be on an identifier." << std::endl;
        }
    }
    ;

primary:
    INT_LIT { $$ = (Expression*)(new IntLiteral($1))->loc(@1.first_line, @1.first_column); }
    | FLOAT_LIT { $$ = (Expression*)(new FloatLiteral($1))->loc(@1.first_line, @1.first_column); }
    | BOOL_LIT { $$ = (Expression*)(new BoolLiteral($1 != 0))->loc(@1.first_line, @1.first_column); }
    | STRING_LIT { $$ = (Expression*)(new StringLiteral(*$1))->loc(@1.first_line, @1.first_column); }
    | IMAG_LIT { $$ = (Expression*)(new ImaginaryLiteral($1))->loc(@1.first_line, @1.first_column); }
    | TIME_LIT { $$ = (Expression*)(new Identifier(*$1))->loc(@1.first_line, @1.first_column); } 
    | ID { $$ = (Expression*)(new Identifier(*$1))->loc(@1.first_line, @1.first_column); }
    | LPAREN expression RPAREN { $$ = $2; }
    | LBRACKET elements RBRACKET {
        $$ = (Expression*)(new ArrayLiteral(*$2))->loc(@1.first_line, @1.first_column);
        delete $2;
    }
    /* Allow Braces { 1, 2 } for Array Literals */
    | LBRACE argument_list RBRACE {
        $$ = (Expression*)(new ArrayLiteral(*$2))->loc(@1.first_line, @1.first_column);
        delete $2;
    }
    ;

elements:
    /* empty */ { $$ = new std::vector<Expression*>(); }
    | argument_list { $$ = $1; }
    ;

argument_list:
    expression { 
        $$ = new std::vector<Expression*>();
        $$->push_back($1); 
    }
    | argument_list COMMA expression {
        $1->push_back($3);
        $$ = $1;
    }
    ;

%%

void yyerror(const YYLTYPE* loc, yyscan_t scanner, Program** root, const char *s) {
    std::cerr << "Parser Error at line " << loc->first_line << ", col " << loc->first_column 
              << ": " << s << std::endl;
}