// tests/test_opt_fusion.qs
qubit q[2];
const PI = 3.14;

// 1. Basic Fusion (Constants)
// rx(1.0) then rx(2.0) -> rx(3.0)
q[0].rx(1.0);
q[0].rx(2.0);


float theta = 0.5;
float phi = 0.1;
q[1].rz(theta);
q[1].rz(phi);

// 2. Loop Unrolling + Fusion
// for i in 0..2 { q[0].ry(0.5); }
// Unrolls to: q[0].ry(0.5); q[0].ry(0.5); q[0].ry(0.5);
// Fuses to: q[0].ry(1.5);
for i in 0..2 {
    q[0].ry(0.5);
}