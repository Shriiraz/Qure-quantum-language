// tests/test_scope.qs
int global_counter = 0;

func complex_logic(flag: bool) {
    int x = 10;
    if (flag) {
        // Shadowing 'x'
        int x = 20;
        qubit ancilla[1];
        ancilla[0].h();
    } else {
        x = 30;
    }
    // 'x' here should refer to the outer x (10 or 30), not inner (20)
    global_counter += x;
}