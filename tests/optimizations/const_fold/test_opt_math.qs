// tests/test_opt_math.qs
const PI = 3.14159;

// 1. Precedence: 2 + (3 * 4) = 14, NOT 20
int order = 2 + 3 * 4; 

// 2. Mixed Types: (2 * 1.5) + 1 = 4.0
float mixed = (2 * 1.5) + 1;

// 3. Angle Math: PI / (2^2) = PI / 4 = 0.78539
// Note: 2 << 1 is 4 (Bitwise shift)
angle theta = PI / (2 << 1);

// 4. Boolean Logic
// (10 > 5) AND (1 != 0) -> true AND true -> true
bool logic = (10 > 5) && (1 != 0);