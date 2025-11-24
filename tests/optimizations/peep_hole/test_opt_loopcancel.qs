// tests/opt_loop_cancel.qs
qubit q[1];

// This loop runs 2 times.
// Unrolled: { q[0].z(); } { q[0].z(); }
// Flattened: q[0].z(); q[0].z();
// Cancelled: (Empty)
for i in 0..1 {
    q[0].z();
}