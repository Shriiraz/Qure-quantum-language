// tests/test_arithmetic.qs
complex alpha = 1.0 + 2.0i;
complex beta = 3.5 - 0.5i;

// Custom Hamiltonian
matrix H = [[ 1, 0 ], 
            [ 0, -1 ]];

// Arithmetic precedence check
complex gamma = alpha * beta + (alpha / 2.0);