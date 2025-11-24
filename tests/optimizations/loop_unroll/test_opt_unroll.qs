// tests/test_opt_unroll.qs
qubit q[3];

// This loop iterates 3 times: 0, 1, 2
for i in 0..2 {
    q[i].h();
}