# Matrix operations ESP IDF component

Simple matrix operations component for ESP IDF and ESP32 microcontrollers.

Usage example:
```c
matrix_t A;
matrix_t B;
matrix_t C;

// allocate matrices
matrix_alloc(&A, 3, 3);
matrix_alloc(&B, 3, 3);
matrix_alloc(&C, 3, 3);

// example matrix operations
matrix_mul(&A, &B, &C);
// (...)


// deallocate matrices
matrix_dealloc(&A);
matrix_dealloc(&B);
matrix_dealloc(&C);
```