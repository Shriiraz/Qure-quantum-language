# Project Configuration
TARGET      = qcc
CXX         = g++
CXXFLAGS    = -std=c++17 -Iinclude -Isrc -Wno-register -Wno-unused-function -O3

# Source Definitions
PARSER_SRC  = src/parser.y
LEXER_SRC   = src/lexer.l
CORE_SRCS   = src/main.cpp src/semantic.cpp src/optimizer.cpp src/codegen.cpp

# Generated Files
GEN_PARSER_C = src/parser.tab.cpp
GEN_PARSER_H = src/parser.tab.hpp
GEN_LEXER_C  = src/lex.yy.cpp

# Dependency Paths
DEPS_DIR    = ./deps
BISON_DIR   = $(DEPS_DIR)/bison-3.8.2
LOCAL_BISON = $(DEPS_DIR)/bin/bison
BISON_URL   = https://ftp.gnu.org/gnu/bison/bison-3.8.2.tar.gz


# 1. Check if we already built a local bison
ifneq ("$(wildcard $(LOCAL_BISON))","")
    BISON_CMD = $(LOCAL_BISON)
    MSG = Using Local Bison (v3.8.2)
else
    # 2. Check System Bison Version
    SYSTEM_BISON_VER := $(shell bison --version 2>/dev/null | head -n 1 | awk '{print $$4}')
    
    # If system bison >= 3.8, use it. Otherwise, default to LOCAL_BISON.
    IS_OLD := $(shell echo "$(SYSTEM_BISON_VER)\n3.8" | sort -V | head -n1)
    
    ifeq ($(IS_OLD),$(SYSTEM_BISON_VER))
        # System is old or missing (< 3.8), use Local
        BISON_CMD = $(LOCAL_BISON)
        MSG = System Bison is too old ($(SYSTEM_BISON_VER)). Using Local Build.
    else
        # System is good (>= 3.8)
        BISON_CMD = bison
        MSG = Using System Bison ($(SYSTEM_BISON_VER))
    endif
endif

FLEX_CMD = flex

#  Build Targets

all: info check_deps $(TARGET)

info:
	@echo "========================================"
	@echo "  Build Info"
	@echo "  Bison Strategy: $(MSG)"
	@echo "  Bison Path:     $(BISON_CMD)"
	@echo "========================================"

# 1. Dependency Check & Auto-Download
$(LOCAL_BISON):
	@echo ">> [DEPS] Bison 3.8+ not found. Downloading and compiling locally..."
	@echo ">> [DEPS] This may take 1-2 minutes, but only happens once."
	@mkdir -p $(DEPS_DIR)
	@cd $(DEPS_DIR) && curl -L -O $(BISON_URL)
	@cd $(DEPS_DIR) && tar -xzf bison-3.8.2.tar.gz
	@echo ">> [DEPS] Configuring Bison..."
	@cd $(BISON_DIR) && ./configure --prefix=$(shell pwd)/$(DEPS_DIR) > /dev/null
	@echo ">> [DEPS] Compiling Bison..."
	@cd $(BISON_DIR) && make > /dev/null
	@cd $(BISON_DIR) && make install > /dev/null
	@echo ">> [DEPS] Bison installed to $(LOCAL_BISON)"

# Trigger dependency check
check_deps:
ifeq ($(BISON_CMD),$(LOCAL_BISON))
	@$(MAKE) $(LOCAL_BISON)
endif

# --- 2. Generate Parser ---
$(GEN_PARSER_C): $(PARSER_SRC)
	@echo ">> [BISON] Generating Parser..."
	@$(BISON_CMD) -d -o $(GEN_PARSER_C) $(PARSER_SRC)

# --- 3. Generate Lexer ---
$(GEN_LEXER_C): $(LEXER_SRC) $(GEN_PARSER_C)
	@echo ">> [FLEX]  Generating Lexer..."
	@$(FLEX_CMD) -o $(GEN_LEXER_C) $(LEXER_SRC)

# --- 4. Compile Executable ---
$(TARGET): $(GEN_PARSER_C) $(GEN_LEXER_C) $(CORE_SRCS)
	@echo ">> [CXX]   Compiling $(TARGET)..."
	@$(CXX) $(CXXFLAGS) $(CORE_SRCS) $(GEN_PARSER_C) $(GEN_LEXER_C) -o $(TARGET)
	@echo ">> [DONE]  Success! Run ./$(TARGET)"

# --- Utility ---
clean:
	rm -f $(TARGET)
	rm -f src/parser.tab.cpp src/parser.tab.hpp src/lex.yy.cpp
	rm -f src/*.o src/location.hh src/position.hh src/stack.hh

clean_deps:
	rm -rf $(DEPS_DIR)

test: $(TARGET)
	./$(TARGET) tests/final_grover.qs

.PHONY: all info check_deps clean clean_deps test