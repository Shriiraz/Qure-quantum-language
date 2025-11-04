// tests/test_qft.qs
const PI = 3.14159;
qubit q[4];

func qft_rotations(n: int) {
    // N = 4 for this example
    for i in 0..4 {
        q[i].h();
        
        // Classical math for rotation angle
        int k = 2;
        
        // Nested Loop
        for j in (i+1)..4 {
            // Math: PI / (2 ^ k)
            // Note: We assume 'rz' is the gate for this test
            angle theta = PI / (2 ** k); 
            q[j].rz(theta);
            
            k = k + 1;
        }
    }
}

// Apply to register
qft_rotations(4);