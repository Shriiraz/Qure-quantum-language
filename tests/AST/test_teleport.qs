// tests/test_teleport.qs
circuit teleport(src: qubit, dest: qubit) {
    qubit ancilla[1];
    bit c[2];

    // Bell Pair Creation
    ancilla[0].h();
    ancilla[0].cnot(dest);

    // Bell Measurement
    src.cnot(ancilla[0]);
    src.h();
    
    // Measurement into classical bits
    c[0] = src.measure();
    c[1] = ancilla[0].measure();

    // Classical Control
    if (c[0] == 1) {
        dest.z();
    }
    if (c[1] == 1) {
        dest.x();
    }
}