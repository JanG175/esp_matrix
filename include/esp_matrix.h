/**
 * @file esp_matrix.h
 * @author JanG175
 * @brief MATRIX OPERATIONS LIBRARY
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "esp_log.h"

// matrix structure with matrix dimensions and array
typedef struct matrix_t
{
    uint32_t rows;
    uint32_t cols;
    double** array;
} matrix_t;


void matrix_alloc(matrix_t* A, uint32_t rows, uint32_t cols);

void matrix_dealloc(matrix_t* A);

void matrix_mul(matrix_t* A, matrix_t* B, matrix_t* C);

void matrix_add(matrix_t* A, matrix_t* B, matrix_t* C);

void matrix_sub(matrix_t* A, matrix_t* B, matrix_t* C);

void matrix_trans(matrix_t* A, matrix_t* B);

double matrix_det(double** A, uint32_t row);

void matrix_inv(matrix_t* A, matrix_t* B);