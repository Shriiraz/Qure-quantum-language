// tests/test_array_loop.qs
qubit q[3];
float angles[3] = {1.1, 2.2, 3.3};

// 1. Iterate over Qubit Array
// 'qb' should be inferred as QUBIT
for qb in q {
    qb.h(); // Valid only if qb is QUBIT
}

// 2. Iterate over Float Array
// 'val' should be inferred as FLOAT
for val in angles {
    // Valid only if val is FLOAT/ANGLE
    q[0].rx(val); 
}

// 3. Array Literal
for k in [0, 2] {
    q[k].x();
}