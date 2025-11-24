qubit q[5];
int x = 1;
float f = 2.0;

// === VALID CASES ===
// 1. Toffoli (2 controls)
q[0].mcx(q[1], q[2]);

// 2. 4-Control NOT
q[4].mcx(q[0], q[1], q[2], q[3]);


// === ERROR CASES (The compiler should report these but continue) ===

// Error 1: mcx requires at least 1 control
q[0].mcx();

// Error 2: Argument is not a qubit (int variable)
q[0].mcx(q[1], x);

// Error 3: Argument is not a qubit (literal)
q[0].mcx(q[1], 3.14);

// Error 4: Multiple invalid arguments
q[0].mcx(x, f);