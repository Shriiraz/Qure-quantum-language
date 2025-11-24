// tests/test_complex_scope.qs
int x = 10; // Global

circuit test_scope() {
    // Local shadows global
    int x = 20; 
    
    parallel(stretch) {
        // Inner shadows local
        int x = 30; 
        qubit q[1];
        
        // Should use inner x (30)
        // We don't have print, but semantically this checks out
        int z = x; 
    }
    
    // Should use local x (20)
    int y = x; 
}

// === ERROR CASES ===

// Error 1: Accessing 'z' which was defined inside parallel block
int leak = z; 

// Error 2: Accessing 'q' which was defined inside parallel block
q[0].h();