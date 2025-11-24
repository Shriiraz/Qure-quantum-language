// tests/final_opt_chain.qs
qubit q[1];
const PI = 3.14159;

// This loop creates: RX(PI/2) -> RX(PI/2) -> RX(PI/2) -> RX(PI/2)
// Total = RX(2*PI) -> Identity (Global Phase ignored)
// BUT our optimizer will fuse it to RX(6.28318).
for i in 0..3 {
    q[0].rx(PI / 2.0);
}

// This creates: H -> H -> H -> H
// Cancellation should wipe ALL of them out.
for k in 0..3 {
    q[0].h();
}

// This creates: Z -> Z -> X -> X -> Z
// Cancellation: (Z Z) -> (X X) -> Z left over.
q[0].z();
q[0].z();
q[0].x();
q[0].x();
q[0].z();