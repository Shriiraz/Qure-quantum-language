/* 
   lexer.l
*/

%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.tab.hpp"

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line = yylineno; \
    yylloc->first_column = current_column; \
    yylloc->last_column = current_column + yyleng - 1; \
    current_column += yyleng;
%}

%option noyywrap
%option yylineno
%option nounput
%option noinput
%option reentrant 
%option bison-bridge 
%option bison-locations

%{
    static thread_local int current_column = 1;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_LIT     {DIGIT}+

/* FLOAT LOGIC SPLIT */
/* Case A: Digits after dot (e.g. 0.5, .5, 1.0) - Always a float */
FLOAT_A     ({DIGIT}+"."{DIGIT}+|{DIGIT}*"."{DIGIT}+)([eE][-+]?{DIGIT}+)?

/* Case B: No digits after dot (e.g. 1., 1.e5) - Ambiguous with Range */
FLOAT_B     {DIGIT}+"."([eE][-+]?{DIGIT}+)?

IMAG_LIT    ({FLOAT_A}|{FLOAT_B}|{INT_LIT})"i"
TIME_LIT    {DIGIT}+(ns|us|ms|s)
STRING_LIT  \"([^"\\]|\\.)*\"

%%

[ \t\r]+    { /* Skip */ }
\n          { current_column = 1; }
"//".* { /* Skip comments */ }

    /* LITERALS (Specifics First) */

/* 1. Safe Floats (e.g. 0.5) */
{FLOAT_A}   { yylval->fval = std::stod(yytext); return FLOAT_LIT; }

/* 2. Ambiguous Floats (e.g. 0.) */
{FLOAT_B}/[^.] { yylval->fval = std::stod(yytext); return FLOAT_LIT; }

/* 3. Imaginary */
{IMAG_LIT} {
    std::string text = yytext;
    text.pop_back();
    yylval->fval = std::stod(text);
    return IMAG_LIT;
}

/* 4. Time */
{TIME_LIT} {
    yylval->sval = new std::string(yytext);
    return TIME_LIT;
}

/* 5. Integers */
{INT_LIT}   { yylval->ival = std::stoi(yytext); return INT_LIT; }

/* KEYWORDS */
"import"    { return KW_IMPORT; }
"const"     { return KW_CONST; }
"var"       { return KW_VAR; }
"let"       { return KW_LET; }

"int"       { return KW_INT; }
"float"     { return KW_FLOAT; }
"angle"     { return KW_ANGLE; }
"bool"      { return KW_BOOL; }
"string"    { return KW_STRING; }
"complex"   { return KW_COMPLEX; }
"matrix"    { return KW_MATRIX; }

"qubit"     { return KW_QUBIT; }
"bit"       { return KW_BIT; }

"func"      { return KW_FUNC; }
"circuit"   { return KW_CIRCUIT; }
"return"    { return KW_RETURN; }

"if"        { return KW_IF; }
"else"      { return KW_ELSE; }
"while"     { return KW_WHILE; }
"for"       { return KW_FOR; }
"foreach"   { return KW_FOREACH; }
"in"        { return KW_IN; }

/* OPERATORS */
"->"        { return ARROW; }
".."        { return RANGE; }

"=="        { return EQ; }
"!="        { return NEQ; }
"<="        { return LTE; }
">="        { return GTE; }
"<"         { return LT; }
">"         { return GT; }

"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }

"<<"        { return LSHIFT; }
">>"        { return RSHIFT; }
"&"         { return BIT_AND; }
"|"         { return BIT_OR; }
"^"         { return BIT_XOR; }
"~"         { return BIT_NOT; }

"**"        { return POWER; }
"+="        { return PLUS_ASSIGN; }
"-="        { return MINUS_ASSIGN; }
"*="        { return MUL_ASSIGN; }
"/="        { return DIV_ASSIGN; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return STAR; }
"/"         { return SLASH; }
"%"         { return PERCENT; }
"="         { return ASSIGN; }

"."         { return DOT; }
","         { return COMMA; }
";"         { return SEMICOLON; }
":"         { return COLON; }
"@"         { return AT; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }

"true"      { yylval->ival = 1; return BOOL_LIT; }
"false"     { yylval->ival = 0; return BOOL_LIT; }

{STRING_LIT} {
    yylval->sval = new std::string(yytext + 1, yyleng - 2);
    return STRING_LIT;
}

{ID} {
    yylval->sval = new std::string(yytext);
    return ID;
}

. {
    std::cerr << "Lexical Error: Unexpected character '" << yytext 
              << "' at line " << yylineno << std::endl;
    exit(1); 
}

%%