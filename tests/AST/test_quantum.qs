// tests/test_quantum.qs
qubit q[2];

circuit teleport(msg: qubit, target: qubit) {
    // Method Chaining: H then CNOT
    msg.h().cnot(target);
    
    barrier;
    
    parallel(box) {
        msg.measure();
        delay 500ns @ target;
    }
}