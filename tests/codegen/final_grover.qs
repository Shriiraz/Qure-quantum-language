// tests/final_grover.qs
const N_QUBITS = 3;
qubit q[3];
qubit ancilla[1];

// 1. Initialization
for i in 0..2 {
    q[i].h();
}
ancilla[0].x();
ancilla[0].h();

// 2. Oracle (Phase Flip on |111>)
// This should generate a multi-controlled X
q[2].mcx(q[0], q[1], ancilla[0]);

// 3. Diffuser (Inversion about Mean)
for i in 0..2 {
    q[i].h();
    q[i].x();
}

// Multi-controlled Z logic (H -> MCX -> H)
q[2].h();
q[2].mcx(q[0], q[1]);
q[2].h();

for i in 0..2 {
    q[i].x();
    q[i].h();
}

// 4. Measurement
bit c[3];
for i in 0..2 {
    c[i] = q[i].measure();
}