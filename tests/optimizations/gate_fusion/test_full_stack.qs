// tests/opt_full_stack.qs
const N = 4;
const THETA = 0.5;
qubit q[N];

// This loop applies:
// i=0: rx(0.5)
// i=1: rx(0.5)
// i=2: rx(0.5)
// i=3: rx(0.5)
// Total: rx(2.0)
for i in 0..(N-1) {
    q[0].rx(THETA);
}

// This sequence:
// 1. H
// 2. Loop (2x H) -> H H -> Identity
// 3. H
// Result: H, Identity, H -> H H -> Identity!
q[1].h();
for k in 0..1 {
    q[1].h();
}
q[1].h();