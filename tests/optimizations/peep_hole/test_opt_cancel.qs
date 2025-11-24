qubit q[2];

// 1. Explicit Cancellation
q[0].h();
q[0].h(); // Should cancel previous

// 2. Interrupted (Should NOT cancel)
q[0].x();
q[1].x(); // Different qubit
q[0].x(); // Back to q[0], but not adjacent in AST?
          // Note: Our optimizer works on AST order. 
          // x, x(other), x -> No cancellation for first x.
          // But the second x and third x? No, q[1] vs q[0].

// 3. Loop Unrolling + Cancellation
// This loop runs 2 times (0, 1).
// Iteration 0: q[0].z()
// Iteration 1: q[0].z()
// Result: q[0].z(); q[0].z() -> Identity!
for i in 0..1 {
    q[0].z();
}

// 4. CNOT Cancellation
q[0].cnot(q[1]);
q[0].cnot(q[1]); // Matches -> Cancel