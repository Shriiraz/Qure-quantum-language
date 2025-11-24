// tests/test_semantic_control.qs
int x = 1;
float f = 0.5;

// Valid: Int as boolean (C-style)
if (x) {
    x = 2;
}

// Valid: Boolean logic
if (x > 0 && true) {
    x = 3;
}

// === ERROR CASES ===

// Error 1: Float in 'if' condition
if (f) { // Error: 'if' condition must be boolean or int
    x = 4;
}

// Error 2: String in 'while' condition
while ("loop") { // Error: 'while' condition must be boolean or int
    x = x + 1;
}