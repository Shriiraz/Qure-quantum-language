// tests/test_semantic_gates.qs
qubit q[2];
float theta = 3.14;
int val = 1;

// Valid Calls
q[0].h();
q[0].rx(theta);
q[0].ry(3.14);
q[0].rz(val); // Int -> Angle implicit cast allowed in logic

// === ERROR CASES ===

// Error 1: Hadamard does not take arguments
q[0].h(theta); 

// Error 2: Rotation expects a Number (Angle/Float/Int), got Qubit
q[0].rx(q[1]); 

// Error 3: CNOT expects a Qubit, got Float
q[0].cnot(theta); 

// Error 4: Multi-control requires valid Qubits
q[0].mcx(q[1], theta);