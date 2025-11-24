// tests/opt_loop_fusion.qs
qubit q[1];

// 4 iterations of 0.25 -> Total 1.0
for i in 0..3 {
    q[0].rx(0.25);
}