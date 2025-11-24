// tests/test_semantic_arrays.qs

// Valid Allocations
qubit q[5];
int arr[3] = {1, 2, 3};
float mat[2] = {1.0, 2.0};

// === ERROR CASES ===

// Error 1: Array size must be Integer (got Float)
qubit bad_q[2.5]; 

// Error 2: Array size must be Integer (got String)
int bad_arr["size"];

// Error 3: Auto inference without initializer
var x;

// 1. Uninitialized Classical Array (Now valid Syntax)
int buffer[10]; 
float weights[5];

// 2. Initialized Array (Standard)
int valid_arr[3] = {1, 2, 3};

// 3. Logic using the array
buffer[0] = 100;
weights[1] = 0.5;

// === ERROR CASES (Semantic) ===

// Error 1: Auto inference requires initializer
var empty_var; 

// Error 2: Const requires initializer
const PI; 

// Error 3: Array size must be integer
int bad_size[2.5];