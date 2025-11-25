# Qure — Quantum Compiler

## A High-Level Optimizing Quantum Compiler

Qure is a compiler for a robust, C-like quantum programming language. It bridges the gap between high-level algorithmic logic and low-level quantum hardware instructions. It allows developers to write quantum algorithms using familiar constructs—variables, loops, functions, and complex arithmetic—and compiles them into optimized OpenQASM 3.0 code ready for execution on quantum simulators or real hardware.

## Architecture & Workflow

The compiler follows a standard multi-pass architecture to ensure safety and efficiency before code generation.

```text
graph TD

A[Source Code .qs] -->|Flex| B(Lexer);

B -->|Bison 3.8+| C(Parser);

C --> D[Abstract Syntax Tree];

D --> E{Semantic Analyzer};

E -->|Error| F[Stop & Report];

E -->|Valid| G[Optimizer];

G -->|Constant Folding| G;

G -->|Loop Unrolling| G;

G -->|Gate Cancellation| H[Optimized AST];

H --> I[Code Generator];

I --> J[OpenQASM 3.0 Output];
```

**Frontend:** Tokenizes input and builds an Abstract Syntax Tree (AST).

**Middle-End (Semantics):** Validates types, scopes, and quantum operations.

**Middle-End (Optimization):** Transforms the AST to reduce instruction count and simplify logic.

**Backend:** Translates the optimized AST into the target OpenQASM 3.0 specification.

## Key Features

1. High-Level Syntax

Mixed Types: Supports Classical (int, float, bool, angle, complex) and Quantum (qubit, bit) types.

Control Flow: Full support for if/else, while, and for loops (including range-based 0..N and array iteration).

Functions: Define reusable logic using func (classical logic) or circuit (quantum operations).

Math: Native support for complex numbers (1 + 2i), matrices, and bitwise operators.

2. Semantic Safety

The compiler enforces strict rules to prevent runtime errors on quantum hardware:

Type Checking: Prevents illegal operations (e.g., using a qubit as a rotation angle).

Scope Management: Handles variable shadowing and ensures variables are defined before use.

Gate Verification: Validates that gates receive the correct number and type of arguments (e.g., mcx requires $\ge 1$ control).

3. Optimization Engine

A powerful pass that mutates the AST to improve performance:

Constant Folding: Evaluates expressions like PI / (2\*\*2) $\rightarrow$ 0.785 at compile time.

Constant Propagation: Replaces const variables with literals deeply throughout the code.

Dead Code Elimination: Removes if(false) blocks and unreachable code.

Loop Unrolling: Flattens loops with constant ranges into linear sequences of gates (critical for hardware timing).

Peephole Optimization:

Gate Cancellation: Removes adjacent self-inverse gates (H + H $\rightarrow$ Identity).

Gate Fusion: Merges sequential rotations (RZ(0.5) + RZ(0.3) $\rightarrow$ RZ(0.8)).

4. Code Generation

OpenQASM 3.0: Generates standard-compliant code.

Gate Modifiers: Automatically translates custom calls like q.mcx(...) into ctrl(...) @ x.

Timing: Supports delay, barrier, and parallel execution blocks.


## Dependencies & Prerequisites

To build the compiler, you need the following tools installed:

C++ Compiler:

Requirement: g++ or clang.

Standard: The project Makefile uses C++17 by default, but the code is compatible with C++11.

Make: Standard build automation tool.

Flex: The Fast Lexical Analyzer Generator.

Bison (v3.8+): The Parser Generator.

Note: macOS usually comes with an old version (2.3). The included Makefile automatically handles this. If it detects an incompatible version, it will download and compile a local copy of Bison 3.8.2 inside the project folder.

## How to Build and Run

1. Build the Compiler

Navigate to the project root and run:

make

This will:

Check for Bison 3.8+. (Auto-downloads if missing).

Generate the parser (parser.tab.cpp) and lexer (lex.yy.cpp).

Compile everything into an executable named qcc.

2. Run a Test

You can compile any .qs file in the tests/ directory:

./qcc tests/final_grover.qs

3. Clean Build Artifacts

To remove generated files and the executable:

make clean

To remove the locally downloaded Bison (if applicable):

make clean_deps

## Example: Grover's Algorithm

### Input (tests/final_grover.qs):

const N = 2;
qubit q[2];
qubit ancilla[1];

// Initialization Loop
for i in 0..(N-1) {
q[i].h();
}

// Oracle (Multi-Controlled X)
q[1].mcx(q[0], ancilla[0]);

// Measurement
bit c[2];
for i in 0..(N-1) {
c[i] = q[i].measure();
}

### Output (Generated OpenQASM 3.0):

OPENQASM 3.0;
include "stdgates.inc";

qubit[2] q;
qubit[1] ancilla;
{
// Loop Unrolled
h q[0];
h q[1];
}
// MCX Translated to Modifier
ctrl(2) @ x q[0], ancilla[0], q[1];
bit[2] c;
{
c[0] = measure q[0];
c[1] = measure q[1];
}

## Example: Quantum Fourier Transform (QFT)

### Input (tests/AST/test_qft.qs):

```qs
const PI = 3.14159;
qubit q[4];

func qft_rotations(n: int) {
		for i in 0..4 {
				q[i].h();
				int k = 2;
				for j in (i+1)..4 {
						angle theta = PI / (2 ** k);
						q[j].rz(theta);
						k = k + 1;
				}
		}
}

qft_rotations(4);
```

### Output (Generated OpenQASM 3.0):

```openqasm
OPENQASM 3.0;
qubit[4] q;
{
	// i = 0
	h q[0];
	rz(PI/4) q[1];
	rz(PI/8) q[2];
	rz(PI/16) q[3];

	// i = 1
	h q[1];
	rz(PI/4) q[2];
	rz(PI/8) q[3];

	// i = 2
	h q[2];
	rz(PI/4) q[3];

	// i = 3
	h q[3];
}
```

---

## Example: Quantum Teleportation

### Input (tests/AST/test_teleport.qs):

```qs
circuit teleport(src: qubit, dest: qubit) {
		qubit ancilla[1];
		bit c[2];

		// Bell pair
		ancilla[0].h();
		ancilla[0].cnot(dest);

		// Bell measurement
		src.cnot(ancilla[0]);
		src.h();

		// Capture results in classical bits
		c[0] = src.measure();
		c[1] = ancilla[0].measure();

		// Conditional corrections
		if (c[0] == 1) {
				dest.z();
		}
		if (c[1] == 1) {
				dest.x();
		}
}
```

### Output (Generated OpenQASM 3.0):

```openqasm
OPENQASM 3.0;
qubit src;
qubit dest;
qubit[1] ancilla;

{
	// Prepare a Bell pair between ancilla and dest
	h ancilla[0];
	cnot ancilla[0], dest;

	// Teleportation steps
	cnot src, ancilla[0];
	h src;
}

bit[2] c;
{
	c[0] = measure src;
	c[1] = measure ancilla[0];
}

// Classical-controlled corrections
if (c[0] == 1) {
	z dest;
}
if (c[1] == 1) {
	x dest;
}
```

## Known Issues & Limitations

Mutable Variable Optimization: The optimizer relies on const declarations for propagation. It does not perform Static Single Assignment (SSA) analysis, so variables that change value (x = x + 1) are not propagated.

Dynamic Loops: Loop unrolling is only performed on loops with bounds known at compile time (0..5). Dynamic loops (0..n) are preserved as standard for loops in QASM, which some hardware controllers may not support.

Adjacency Requirement: Gate cancellation is strictly peephole-based. It removes H followed immediately by H, but cannot look past intervening gates even if they commute.

Hardware Topology: The compiler assumes all-to-all connectivity. It does not insert SWAP gates to map the circuit to specific chip architectures (e.g., linear or heavy-hex).

## Project Structure

QCompiler/
├── include/
│ ├── ast.hpp # Abstract Syntax Tree Classes
│ ├── semantic.hpp # Type Checking & Symbol Table
│ ├── optimizer.hpp # Folding, Unrolling, Fusion Passes
│ └── codegen.hpp # OpenQASM 3.0 Translator
├── src/
│ ├── lexer.l # Flex Tokenizer Definitions
│ ├── parser.y # Bison Grammar Rules
│ ├── semantic.cpp # Semantic Analysis Implementation
│ ├── optimizer.cpp # Optimization Logic
│ ├── codegen.cpp # Code Generation Implementation
│ └── main.cpp # Compiler Driver
├── tests/ # Test Suite (.qs files)
└── Makefile # Cross-Platform Build Script

### Still working on
- Adding support for hardware topology