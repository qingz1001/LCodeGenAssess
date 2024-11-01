#include <stdio.h>
#include <stdlib.h>

#define MOD 65521

int det(int** matrix, int size) {
    if (size == 1) return matrix[0][0];
    if (size == 2) return (matrix[0][0] * matrix[1][1]) % MOD - (matrix[0][1] * matrix[1][0]) % MOD;

    int det_val = 0;
    for (int col = 0; col < size; col++) {
        int** sub_matrix = (int**)malloc((size - 1) * sizeof(int*));
        for (int i = 1; i < size; i++) {
            sub_matrix[i - 1] = (int*)malloc((size - 1) * sizeof(int));
            for (int j = 0; j < size; j++) {
                if (j < col) sub_matrix[i - 1][j] = matrix[i][j];
                else sub_matrix[i - 1][j] = matrix[i][j + 1];
            }
        }
        det_val += ((col % 2 == 0 ? 1 : -1)) * matrix[0][col] * det(sub_matrix, size - 1);
        for (int i = 1; i < size; i++) free(sub_matrix[i - 1]);
        free(sub_matrix);
    }
    return (det_val + MOD) % MOD;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    int** A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        A[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) A[i][j] = n - 1;
            else if (abs(i - j) <= k) A[i][j] = -1;
            else A[i][j] = 0;
        }
    }

    int** B = (int**)malloc((n - 1) * sizeof(int*));
    for (int i = 0; i < n - 1; i++) {
        B[i] = (int*)malloc((n - 1) * sizeof(int));
        for (int j = 0; j < n - 1; j++) {
            B[i][j] = A[i + 1][j + 1];
        }
    }

    int result = det(B, n - 1);
    printf("%d\n", result);

    for (int i = 0; i < n; i++) free(A[i]);
    free(A);
    for (int i = 0; i < n - 1; i++) free(B[i]);
    free(B);

    return 0;
}