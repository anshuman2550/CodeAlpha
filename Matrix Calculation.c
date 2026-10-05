#include <stdio.h>

#define MAX 10

int inputMatrix(int matrix[MAX][MAX], int rows, int cols);
int displayMatrix(int matrix[MAX][MAX], int rows, int cols);
int addMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int r2, int c2);
int multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int r2, int c2);
int transposeMatrix(int src[MAX][MAX], int dest[MAX][MAX], int r, int c);

int main() {
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2;

    printf("Enter rows and columns for Matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter elements of Matrix A:\n");
    inputMatrix(A, r1, c1);

    printf("\nEnter rows and columns for Matrix B: ");
    scanf("%d %d", &r2, &c2);
    printf("Enter elements of Matrix B:\n");
    inputMatrix(B, r2, c2);

    // 1. Matrix Addition
    printf("\n--- 1. Matrix Addition (A + B) ---\n");
    if (addMatrices(A, B, result, r1, c1, r2, c2)) {
        displayMatrix(result, r1, c1);
    } else {
        printf("Error: Matrix addition requires identical dimensions (%dx%d vs %dx%d).\n", r1, c1, r2, c2);
    }

    // 2. Matrix Multiplication
    printf("\n--- 2. Matrix Multiplication (A * B) ---\n");
    if (multiplyMatrices(A, B, result, r1, c1, r2, c2)) {
        displayMatrix(result, r1, c2);
    } else {
        printf("Error: Matrix multiplication requires columns of A (%d) == rows of B (%d).\n", c1, r2);
    }

    // 3. Matrix Transpose
    printf("\n--- 3. Transpose of Matrix A ---\n");
    transposeMatrix(A, result, r1, c1);
    displayMatrix(result, c1, r1);

    return 0;
}

int inputMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return 1;
}

int displayMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int addMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int r2, int c2) {
    // Dimension check
    if (r1 != r2 || c1 != c2) {
        return 0; // Failure
    }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return 1; // Success
}

int multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int r2, int c2) {
    // Dimension check
    if (c1 != r2) {
        return 0; // Failure
    }
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return 1; // Success
}

int transposeMatrix(int src[MAX][MAX], int dest[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            dest[j][i] = src[i][j];
        }
    }
    return 1;
}