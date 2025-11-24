// tests/test_opt_loops.qs
const N = 4;
qubit q[4];

// Loop range should fold: 0 .. (4-1) -> 0..3
for i in 0..(N - 1) {
    
    // Inside the loop, we can't fold 'i' yet (that's loop unrolling),
    // but we CAN fold the static parts around it.
    
    // q[0 + 1] -> q[1] (Static index check)
    q[0 + 1].x();
    
    // Complex static index
    // (2 * 2) - 1 -> 3
    q[(2 * 2) - 1].h();
}