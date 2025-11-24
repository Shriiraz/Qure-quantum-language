// tests/test_const_quantum.qs
qubit q[2];
const PI = 3.14159;

circuit test_optimization(t: qubit) {
    // 1. Fold inside gate argument
    // 3.14159 / 2.0 -> 1.570795
    t.rx(PI / 2.0); 

    // 2. Fold inside array index
    // q[1+0] -> q[1]
    q[1 + 0].h();
    
    // 3. Complex folding
    // (2 * 2) -> 4
    q[0].rz(PI / (2 * 2));
}