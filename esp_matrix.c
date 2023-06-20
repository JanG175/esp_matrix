/**
 * @file esp_matrix.c
 * @author JanG175
 * @brief MATRIX OPERATIONS LIBRARY
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "esp_matrix.h"

static const char *TAG = "esp_matrix";


/**
 * @brief allocate memory for matrix
 * 
 * @param A pointer to matrix struct
 * @param rows number of matrix rows
 * @param cols number of matrix columns
 */
void matrix_alloc(matrix_t* A, uint32_t rows, uint32_t cols)
{
    A->rows = rows;
    A->cols = cols;
    A->array = NULL;

    A->array = (float**)malloc(A->rows * sizeof(float*));
    for (uint32_t i = 0; i < A->rows; i++)
        A->array[i] = (float*)malloc(A->cols * sizeof(float));
}


/**
 * @brief free memory of matrix
 * 
 * @param A pointer to matrix struct
 */
void matrix_dealloc(matrix_t* A)
{
    for (uint32_t i = 0; i < A->rows; i++)
        free(A->array[i]);
    free(A->array);
    A->array = NULL;

    A->rows = 0;
    A->cols = 0;
}


/**
 * @brief multiply two matrices
 * 
 * @param A matrix A
 * @param B matrix B
 * @param C matrix C = A * B
 */
void matrix_mul(matrix_t A, matrix_t B, matrix_t* C)
{
    if (A.cols != B.rows || A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0)
    {
        C->rows = 0;
        C->cols = 0;
        C->array = NULL;

        ESP_LOGE(TAG, "Wrong array dimensions to mul!");
    }

    C->rows = A.rows;
    C->cols = B.cols;

    C->array = (float**)realloc(C->array, C->rows * sizeof(float*));
    for (uint32_t i = 0; i < C->rows; i++)
        C->array[i] = (float*)realloc(C->array[i], C->cols * sizeof(float));

    for (uint32_t i = 0; i < C->rows; i++)
        for (uint32_t j = 0; j < C->cols; j++)
            C->array[i][j] = 0.0f;

    for (uint32_t i = 0; i < C->rows; i++)
        for (uint32_t j = 0; j < C->cols; j++)
            for (uint32_t k = 0; k < A.cols; k++)
                C->array[i][j] = A.array[i][k] * B.array[k][j] + C->array[i][j];
}


/**
 * @brief add two matrices
 * 
 * @param A matrix A
 * @param B matrix B
 * @param C matrix C = A + B
 */
void matrix_add(matrix_t A, matrix_t B, matrix_t* C)
{
    if (A.rows != B.rows || A.cols != B.cols || A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0)
    {
        C->rows = 0;
        C->cols = 0;
        C->array = NULL;

        ESP_LOGE(TAG, "Wrong array dimensions to add!");
    }

    C->rows = A.rows;
    C->cols = B.cols;

    C->array = (float**)realloc(C->array, C->rows * sizeof(float*));
    for (uint32_t i = 0; i < C->rows; i++)
        C->array[i] = (float*)realloc(C->array[i], C->cols * sizeof(float));

    for (uint32_t i = 0; i < C->rows; i++)
        for (uint32_t j = 0; j < C->cols; j++)
            C->array[i][j] = A.array[i][j] + B.array[i][j];
}


/**
 * @brief subtract two matrices
 * 
 * @param A matrix A
 * @param B matrix B
 * @param C matrix C = A - B
 */
void matrix_sub(matrix_t A, matrix_t B, matrix_t* C)
{
    if (A.rows != B.rows || A.cols != B.cols || A.rows == 0 || A.cols == 0 || B.rows == 0 || B.cols == 0)
    {
        C->rows = 0;
        C->cols = 0;
        C->array = NULL;

        ESP_LOGE(TAG, "Wrong array dimensions to sub!");
    }

    C->rows = A.rows;
    C->cols = B.cols;

    C->array = (float**)realloc(C->array, C->rows * sizeof(float*));
    for (uint32_t i = 0; i < C->rows; i++)
        C->array[i] = (float*)realloc(C->array[i], C->cols * sizeof(float));

    for (uint32_t i = 0; i < C->rows; i++)
        for (uint32_t j = 0; j < C->cols; j++)
            C->array[i][j] = A.array[i][j] - B.array[i][j];
}


/**
 * @brief transpose matrix
 * 
 * @param A matrix A
 * @param B matrix B = A^T
 */
void matrix_trans(matrix_t A, matrix_t* B)
{
    if (A.rows == 0 || A.cols == 0)
    {
        B->rows = 0;
        B->cols = 0;
        B->array = NULL;

        ESP_LOGE(TAG, "Wrong array dimensions to trans!");
    }

    B->rows = A.cols;
    B->cols = A.rows;

    B->array = (float**)realloc(B->array, B->rows * sizeof(float*));
    for (uint32_t i = 0; i < B->rows; i++)
        B->array[i] = (float*)realloc(B->array[i], B->cols * sizeof(float));

    for (uint32_t i = 0; i < B->rows; i++)
        for (uint32_t j = 0; j < B->cols; j++)
            B->array[i][j] = A.array[j][i];
}


/**
 * @brief calculate the determinant of a matrix
 * 
 * @param A matrix A array
 * @param row matrix row
 * @return determinant of matrix A
 */
float matrix_det(float** A, uint32_t row)
{
    float** B = NULL;
    float det = 0.0f;

    B = (float**)malloc(row * sizeof(float*));
    for (uint32_t i = 0; i < row; i++)
        B[i] = (float*)malloc(row * sizeof(float));

    if (row == 1)
    {
        det = A[0][0];
    }
    else
    {
        float s = 1.0f;

        for (uint32_t c = 0; c < row; c++)
        {
            uint32_t m = 0;
            uint32_t n = 0;

            for (uint32_t i = 0; i < row; i++)
            {
                for (uint32_t j = 0; j < row; j++)
                {
                    B[i][j] = 0.0f;
                    if (i != 0 && j != c)
                    {
                        B[m][n] = A[i][j];
                        if (n < (row - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (A[0][c] * matrix_det(B, row - 1));
            s = -1.0f * s;
        }
    }

    for (uint32_t i = 0; i < row; i++)
        free(B[i]);
    free(B);
    B = NULL;

    return det;
}


/**
 * @brief calculate the inverse of a matrix
 * 
 * @param A matrix A
 * @param B matrix B = A^(-1)
 */
void matrix_inv(matrix_t A, matrix_t* B)
{
    if (A.rows != A.cols || A.rows == 0 || A.cols == 0)
    {
        B->rows = 0;
        B->cols = 0;
        B->array = NULL;

        ESP_LOGE(TAG, "Wrong array dimensions to inv!");
    }

    // find determinant
    float A_det = matrix_det(A.array, A.rows);

    if (A_det == 0.0f)
    {
        B->rows = 0;
        B->cols = 0;

        ESP_LOGE(TAG, "Array determinant equal 0!");
    }

    B->rows = A.rows;
    B->cols = A.cols;

    B->array = (float**)realloc(B->array, B->rows * sizeof(float*));
    for (uint32_t i = 0; i < B->rows; i++)
        B->array[i] = (float*)realloc(B->array[i], B->cols * sizeof(float));

    if (A.rows == 1)
    {
        B->array[0][0] = 1 / A.array[0][0];
    }
    else
    {
        // find minors
        matrix_t A_adj;
        A_adj.array = NULL;
        A_adj.rows = A.rows;
        A_adj.cols = A.cols;
        A_adj.array = (float**)malloc(A_adj.rows * sizeof(float*));
        for (uint32_t i = 0; i < A_adj.rows; i++)
            A_adj.array[i] = (float*)malloc(A_adj.cols * sizeof(float));

        matrix_t minor;
        minor.array = NULL;
        minor.rows = A.rows - 1;
        minor.cols = A.cols - 1;
        minor.array = (float**)malloc(minor.rows * sizeof(float*));
        for (uint32_t i = 0; i < minor.rows; i++)
            minor.array[i] = (float*)malloc(minor.cols * sizeof(float));

        for (uint32_t i = 0; i < A.rows; i++)
        {
            for (uint32_t j = 0; j < A.cols; j++)
            {
                uint32_t k = 0;

                for (uint32_t m = 0; m < A.rows; m++)
                {
                    uint32_t l = 0;

                    for (uint32_t n = 0; n < A.cols; n++)
                    {
                        if (m == i)
                            k = 1;
                        if (n == j)
                            l = 1;

                        if (m != i && n != j)
                            minor.array[m - k][n - l] = A.array[m][n];
                    }
                }

                float minus = 1.0f;
                if ((i + j) % 2 != 0)
                {
                    minus = -1.0f;
                }

                A_adj.array[i][j] = minus * matrix_det(minor.array, minor.rows);
            }
        }

        for (uint32_t i = 0; i < minor.rows; i++)
            free(minor.array[i]);
        free(minor.array);
        minor.array = NULL;

        // transpose
        matrix_trans(A_adj, &A_adj);

        for (uint32_t i = 0; i < B->rows; i++)
            for (uint32_t j = 0; j < B->cols; j++)
                B->array[i][j] = 1 / A_det * A_adj.array[i][j];

        for (uint32_t i = 0; i < A_adj.rows; i++)
            free(A_adj.array[i]);
        free(A_adj.array);
        A_adj.array = NULL;
    }
}