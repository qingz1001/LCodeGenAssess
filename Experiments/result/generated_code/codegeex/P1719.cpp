#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

int max_sum(int **matrix, int n) {
    int max = matrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                int row_sum = 0;
                for (int l = i; l <= j; l++) {
                    row_sum += matrix[l][k];
                }
                sum += row_sum;
                if (sum > max) {
                    max = sum;
                }
            }
        }
    }
    return max;
}

int main() {
    int n;
    scanf("%d", &n);
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    int result = max_sum(matrix, n);
    printf("%d\n", result);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}