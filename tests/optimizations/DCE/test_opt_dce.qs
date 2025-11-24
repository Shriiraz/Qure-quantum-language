// tests/test_opt_dce.qs
int x = 0;

// 1. False Condition (Should be removed)
if (10 < 5) {
    x = 666; // Dead Code
}

// 2. True Condition (Should stay)
if (1 == 1) {
    x = 1;
}

// 3. Propagated False Condition
const A = 10;
const B = 20;
if (A > B) {
    x = 999; // Dead Code (10 > 20 is false)
}