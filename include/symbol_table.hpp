#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "ast.hpp"

struct SymbolInfo {
    std::string name;
    DataType type;
    bool isArray;
    int arraySize;      // 0 if scalar
    bool isConst;
    bool isFunction;    // true for func/circuit
    std::vector<DataType> paramTypes; // If function
};

class SymbolTable {
private:
    // Stack of scopes. Each scope is a map of Name -> Symbol
    std::vector<std::map<std::string, SymbolInfo>> scopes;

public:
    SymbolTable() {
        enterScope(); // Create global scope
    }

    void enterScope() {
        scopes.push_back({});
    }

    void exitScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
        }
    }

    // Add symbol to the CURRENT scope
    bool declare(const SymbolInfo& symbol) {
        if (scopes.empty()) return false;
        auto& currentScope = scopes.back();
        
        // Check if already exists in THIS scope (redeclaration error)
        if (currentScope.find(symbol.name) != currentScope.end()) {
            return false; 
        }
        
        currentScope[symbol.name] = symbol;
        return true;
    }

    // Look up symbol (start from top of stack and go down)
    SymbolInfo* lookup(const std::string& name) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto& scope = *it;
            if (scope.find(name) != scope.end()) {
                return &scope[name];
            }
        }
        return nullptr;
    }
};