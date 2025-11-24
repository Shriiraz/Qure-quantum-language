// tests/test_opt_propagation.qs

// 1. Base Constants
const BASE = 10;
const SCALE = 2;

// 2. First Level Propagation (BASE * SCALE) -> 20
const STEP_1 = BASE * SCALE;

// 3. Second Level Propagation (STEP_1 + 5) -> 25
// The optimizer must know STEP_1 is 20 to resolve this.
int final_result = STEP_1 + 5;


if (final_result == 25) {
    int success = 1;
}

if (final_result > 100) {
    int failure = 1;
}