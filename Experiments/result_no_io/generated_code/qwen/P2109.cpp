#include <stdio.h>
#include <stdlib.h>

#define MOD 65521

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

int determinant(int n, int** matrix) {
    if (n == 1) return matrix[0][0];
    if (n == 2) return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;

    int det = 0;
    for (int col = 0; col < n; col++) {
        int** submatrix = (int**)malloc((n-1) * sizeof(int*));
        for (int i = 1; i < n; i++) {
            submatrix[i-1] = (int*)malloc((n-1) * sizeof(int));
            int subcol = 0;
            for (int j = 0; j < n; j++) {
                if (j != col) {
                    submatrix[i-1][subcol++] = matrix[i][j];
                }
            }
        }

        det += ((col % 2 == 0 ? 1 : -1) * matrix[0][col] * determinant(n-1, submatrix)) % MOD;

        for (int i = 1; i < n; i++) {
            free(submatrix[i-1]);
        }
        free(submatrix);
    }
    return det;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    int** A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                A[i][j] = 2 * k + 1;
            } else if (abs(i - j) == 1 || abs(i - j) == 2) {
                A[i][j] = -1;
            } else {
                A[i][j] = 0;
            }
        }
    }

    int** B = (int**)malloc((n-1) * sizeof(int*));
    for (int i = 0; i < n-1; i++) {
        B[i] = (int*)malloc((n-1) * sizeof(int));
        for (int j = 0; j < n-1; j++) {
            B[i][j] = A[i+1][j+1];
        }
    }

    int det_B = determinant(n-1, B);

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < n-1; i++) {
        free(B[i]);
    }
    free(B);

    printf("%d\n", det_B);

    return 0;
}