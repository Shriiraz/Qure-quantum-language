// tests/test_opt_prop.qs

// 1. Base Constants
const BASE = 100;
const OFFSET = 50;

// 2. Dependent Constant (Should become 150)
const TARGET = BASE + OFFSET; 

// 3. Usage in mutable variable
// Should become: int x = 300; (150 * 2)
int x = TARGET * 2;

// 4. Usage in Logic
// Should become: if (true) ...
if (x == 300) {
    // This inner math should also fold
    // 300 + 1 -> 301
    x = x + 1;
}