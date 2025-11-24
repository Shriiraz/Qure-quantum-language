// tests/test_const_arithmetic.qs

// 1. Integer Math
int a = 10 + 5 * 2;        // Should fold to: 20
int b = (10 + 2) / 3;      // Should fold to: 4
int c = 2 ** 3;            // Should fold to: 8

// 2. Float Math
float f1 = 1.5 + 2.5;      // Should fold to: 4.0
float f2 = 10.0 / 4.0;     // Should fold to: 2.5

// 3. Mixed Math (Int + Float)
float m1 = 2 * 1.5;        // Should fold to: 3.0
float m2 = 1 + 0.5;        // Should fold to: 1.5

// 4. Bitwise Operations
int shift = 1 << 3;        // Should fold to: 8