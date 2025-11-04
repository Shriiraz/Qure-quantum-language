// tests/test_flow.qs
qubit q[5];
int i = 0;

if (i < 5) {
    for k in 0..4 {
        q[k].h();
    }
} else {
    // Slicing
    q[1..3].x(); 
}

while (i < 10) {
    i = i + 1;
}