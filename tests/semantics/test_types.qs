// Valid Implicit Casting
float f = 10;          // Int -> Float (Allowed)
complex c = 5;         // Int -> Complex (Allowed)
complex d = 2.5;       // Float -> Complex (Allowed)

// Valid Arithmetic
float res = f + 5;     // Float + Int -> Float

// === ERROR CASES ===

// Error 1: Unsafe downcasting
int x = 2.5;           // Float -> Int (Should be Error)

// Error 2: Type mismatch in assignment
int y = 0;
y = "hello";           // String -> Int (Error)

// Error 3: Quantum to Classical mismatch
qubit q[1];
int z = q[0];          // Qubit -> Int (Error, unless measuring)

// Error 4: Bool logic on Floats
bool b = (5.5 && 2.0); // Logical AND expects Bool/Int, not Float