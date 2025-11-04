// tests/test_math.qs
matrix I = [[1, 0], [0, 1]];
complex z = 0.707 + 0.707i;

int flags = 5; // 0101
int mask = 3;  // 0011
int result = (flags & mask) << 1;

result += 10;