#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Multiply 2 100x100 matrices using OpenMP
int main() {
    int i, j, k;
    double A[100][100], B[100][100], C[100][100];
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
        A[i][j] = i + j;
        B[i][j] = i - j;
        C[i][j] = 0;
        }
    }
    // Perform matrix multiplication
    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            for (k = 0; k < 100; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    // Print results
    printf("\n");
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
        printf("%lf\t", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}