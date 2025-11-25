/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 12 "src/parser.y"

    #include "../include/ast.hpp"
    typedef void* yyscan_t; 

#line 54 "src/parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_LIT = 258,                 /* INT_LIT  */
    BOOL_LIT = 259,                /* BOOL_LIT  */
    FLOAT_LIT = 260,               /* FLOAT_LIT  */
    IMAG_LIT = 261,                /* IMAG_LIT  */
    STRING_LIT = 262,              /* STRING_LIT  */
    ID = 263,                      /* ID  */
    TIME_LIT = 264,                /* TIME_LIT  */
    KW_IMPORT = 265,               /* KW_IMPORT  */
    KW_CONST = 266,                /* KW_CONST  */
    KW_VAR = 267,                  /* KW_VAR  */
    KW_LET = 268,                  /* KW_LET  */
    KW_INT = 269,                  /* KW_INT  */
    KW_FLOAT = 270,                /* KW_FLOAT  */
    KW_ANGLE = 271,                /* KW_ANGLE  */
    KW_BOOL = 272,                 /* KW_BOOL  */
    KW_STRING = 273,               /* KW_STRING  */
    KW_COMPLEX = 274,              /* KW_COMPLEX  */
    KW_MATRIX = 275,               /* KW_MATRIX  */
    KW_QUBIT = 276,                /* KW_QUBIT  */
    KW_BIT = 277,                  /* KW_BIT  */
    KW_FUNC = 278,                 /* KW_FUNC  */
    KW_CIRCUIT = 279,              /* KW_CIRCUIT  */
    KW_RETURN = 280,               /* KW_RETURN  */
    KW_ALIAS = 281,                /* KW_ALIAS  */
    KW_IF = 282,                   /* KW_IF  */
    KW_ELSE = 283,                 /* KW_ELSE  */
    KW_WHILE = 284,                /* KW_WHILE  */
    KW_FOR = 285,                  /* KW_FOR  */
    KW_FOREACH = 286,              /* KW_FOREACH  */
    KW_IN = 287,                   /* KW_IN  */
    KW_PARALLEL = 288,             /* KW_PARALLEL  */
    KW_STRETCH = 289,              /* KW_STRETCH  */
    KW_BOX = 290,                  /* KW_BOX  */
    KW_DELAY = 291,                /* KW_DELAY  */
    KW_BARRIER = 292,              /* KW_BARRIER  */
    ARROW = 293,                   /* ARROW  */
    RANGE = 294,                   /* RANGE  */
    DOT = 295,                     /* DOT  */
    COMMA = 296,                   /* COMMA  */
    SEMICOLON = 297,               /* SEMICOLON  */
    COLON = 298,                   /* COLON  */
    AT = 299,                      /* AT  */
    LPAREN = 300,                  /* LPAREN  */
    RPAREN = 301,                  /* RPAREN  */
    LBRACE = 302,                  /* LBRACE  */
    RBRACE = 303,                  /* RBRACE  */
    LBRACKET = 304,                /* LBRACKET  */
    RBRACKET = 305,                /* RBRACKET  */
    LOWER_THAN_ELSE = 306,         /* LOWER_THAN_ELSE  */
    ASSIGN = 307,                  /* ASSIGN  */
    PLUS_ASSIGN = 308,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 309,            /* MINUS_ASSIGN  */
    MUL_ASSIGN = 310,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 311,              /* DIV_ASSIGN  */
    OR = 312,                      /* OR  */
    AND = 313,                     /* AND  */
    BIT_OR = 314,                  /* BIT_OR  */
    BIT_XOR = 315,                 /* BIT_XOR  */
    BIT_AND = 316,                 /* BIT_AND  */
    EQ = 317,                      /* EQ  */
    NEQ = 318,                     /* NEQ  */
    LT = 319,                      /* LT  */
    GT = 320,                      /* GT  */
    LTE = 321,                     /* LTE  */
    GTE = 322,                     /* GTE  */
    LSHIFT = 323,                  /* LSHIFT  */
    RSHIFT = 324,                  /* RSHIFT  */
    PLUS = 325,                    /* PLUS  */
    MINUS = 326,                   /* MINUS  */
    STAR = 327,                    /* STAR  */
    SLASH = 328,                   /* SLASH  */
    PERCENT = 329,                 /* PERCENT  */
    POWER = 330,                   /* POWER  */
    NOT = 331,                     /* NOT  */
    BIT_NOT = 332,                 /* BIT_NOT  */
    UMINUS = 333                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "src/parser.y"

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

#line 166 "src/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (yyscan_t scanner, Program** root);


#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
