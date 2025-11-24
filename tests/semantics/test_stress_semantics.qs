// tests/test_stress_semantics.qs
qubit q[2];
int i = 10;
float f = 2.5;

// 1. Gate Errors
q[0].h(i);          // Error: H takes 0 args
q[0].rx(q[1]);      // Error: Rx takes Angle, got Qubit
q[0].cnot(i);       // Error: CNOT target must be Qubit
q[0].mcx();         // Error: MCX needs >0 controls

// 2. Type Errors
int arr[2] = {1, 2};
arr[0] = q[0];      // Error: Assign Qubit to Int
if (f) {}           // Error: If condition must be Int/Bool

// 3. Array Errors
qubit bad_q[f];     // Error: Size must be Int
int bad_init[2] = {1.5, 2.5}; // Error: Type mismatch in initializer (Float->Int)

// 4. Logic Errors
int res = 5 && 2;   // OK (Ints are truthy)
bool bad_logic = 5.5 || 2.2; // Error: Logic on floats