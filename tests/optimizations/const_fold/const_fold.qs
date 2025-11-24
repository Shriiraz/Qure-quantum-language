int x = 2 + 3;           // Should become: int x = 5;
float y = 3.14 * 2.0;    // Should become: float y = 6.28;
int z = (2 + 2) * 3;     // Should become: int z = 12;

if (10 > 5) {            // Condition becomes: true
    x = 100;
}

if (1 == 0) {            // Condition becomes: false
    x = -1;              // This block should effectively be dead code
}