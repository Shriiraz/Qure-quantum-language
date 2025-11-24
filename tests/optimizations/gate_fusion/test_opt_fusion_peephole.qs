// tests/opt_basic_peephole.qs
qubit q[2];

// 1. Cancellation: H H -> Identity
q[0].h();
q[0].h();

// 2. Cancellation: CNOT CNOT -> Identity
// (Must match both control and target)
q[0].cnot(q[1]);
q[0].cnot(q[1]);

// 3. Fusion: RX(1.0) + RX(2.0) -> RX(3.0)
q[1].rx(1.0);
q[1].rx(2.0);

// 4. Fusion: RZ with Constants
// RZ(PI/2) + RZ(PI/2) -> RZ(PI) -> RZ(3.14159...)
const PI = 3.14159;
q[0].rz(PI / 2.0);
q[0].rz(PI / 2.0);