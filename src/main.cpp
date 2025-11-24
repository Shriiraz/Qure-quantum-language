#include <iostream>
#include <cstdio>
#include "../include/ast.hpp"
#include "../include/semantic.hpp"
#include "../include/optimizer.hpp"
#include "../include/codegen.hpp"
#include "parser.tab.hpp"

typedef void* yyscan_t;
extern int yylex_init(yyscan_t* scanner);
extern int yylex_destroy(yyscan_t scanner);
extern void yyset_in(FILE* in_str, yyscan_t scanner);
extern int yyparse(yyscan_t scanner, Program** root);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    FILE* myfile = fopen(argv[1], "r");
    if (!myfile) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    yyscan_t scanner;
    if (yylex_init(&scanner) != 0) return 1;

    yyset_in(myfile, scanner);
    Program* root = nullptr;

    int result = yyparse(scanner, &root);
    yylex_destroy(scanner);
    fclose(myfile);

    if (result == 0 && root) {
        SemanticAnalyzer analyzer;
        if (analyzer.analyze(root)) {
            
            Optimizer opt;
            opt.optimize(root);
            
            // --- CODE GENERATION ---
            // Output directly to stdout
            CodeGenerator codegen(std::cout);
            codegen.generate(root);
            
        } else {
            return 1;
        }
    } else {
        return 1;
    }

    return 0;
}