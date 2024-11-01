#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int n, m;
    scanf("%d %d", &m, &n);

    int **matrix = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int **dp = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
    }

    int start_col = n / 2;

    // Initialize the last row of dp array
    for (int j = 0; j < n; j++) {
        dp[m-1][j] = matrix[m-1][j];
    }

    // Fill the dp array
    for (int i = m-2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int max_energy = dp[i+1][j];
            if (j > 0) {
                max_energy = MAX(max_energy, dp[i+1][j-1]);
            }
            if (j < n-1) {
                max_energy = MAX(max_energy, dp[i+1][j+1]);
            }
            dp[i][j] = matrix[i][j] + max_energy;
        }
    }

    // The maximum energy value is at the starting point
    int max_energy = dp[0][start_col];

    printf("%d\n", max_energy);

    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
        free(dp[i]);
    }
    free(matrix);
    free(dp);

    return 0;
}