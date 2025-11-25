#include <iostream>
#include <cstdio>
#include <fstream>
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

    const char* inputFile = argv[1];
    FILE* myfile = fopen(inputFile, "r");
    if (!myfile) {
        std::cerr << "Error: Could not open file " << inputFile << std::endl;
        return 1;
    }

    // Initialize Lexer/Parser
    yyscan_t scanner;
    if (yylex_init(&scanner) != 0) {
        std::cerr << "Error initializing scanner." << std::endl;
        fclose(myfile);
        return 1;
    }

    yyset_in(myfile, scanner);
    Program* root = nullptr;

    //  Parse
    int result = yyparse(scanner, &root);
    yylex_destroy(scanner);
    fclose(myfile);

    if (result == 0 && root) {
        // Semantic Analysis
        SemanticAnalyzer analyzer;
        if (analyzer.analyze(root)) {
            
            // Optimization
            Optimizer opt;
            opt.optimize(root);
            
            // Code Generation
            std::ofstream outFile("output.qasm");
            
            if (!outFile.is_open()) {
                std::cerr << "Error: Could not write to output.qasm" << std::endl;
                return 1;
            }

            CodeGenerator codegen(outFile);
            codegen.generate(root);
            
            outFile.close();
            
            // Success Message
            std::cout << "Successfully compiled " << inputFile << " -> output.qasm" << std::endl;
            
        } else {
            // Semantic errors are printed inside analyzer
            return 1;
        }
    } else {
        std::cerr << "Parsing Failed." << std::endl;
        return 1;
    }

    return 0;
}