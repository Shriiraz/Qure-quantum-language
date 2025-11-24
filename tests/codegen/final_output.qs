qubit q[2];
bit c[2];
const PI = 3.14159;

// This loop will be unrolled and fused!
for i in 0..1 {
    q[i].rx(PI/2.0);
    q[i].rx(PI/2.0);
}

// Measurement
c[0] = q[0].measure();
if (c[0] == 1) {
    q[1].x();
}