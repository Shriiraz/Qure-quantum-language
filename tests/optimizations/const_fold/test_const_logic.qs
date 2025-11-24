// tests/test_const_logic.qs
int x = 0;

// 1. True Condition
if (10 > 5) {
    x = 1;
}

// 2. False Condition (Dead Code)
// The optimizer should see (1 == 0) -> false
// It should then ideally remove this block or just return the 'else' (which is empty)
if (1 == 0) {
    x = 666; // This should disappear from the AST
}

// 3. Logic in Variable
bool is_equal = (5 == 5); // Should fold to: true
bool is_neq = (5 != 5);   // Should fold to: false