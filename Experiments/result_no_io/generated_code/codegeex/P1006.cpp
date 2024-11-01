#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

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

    // Initialize dp array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    // Calculate maximum path sum for reaching (i, j)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[i][j];
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] + matrix[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] + matrix[i][j];
            } else {
                dp[i][j] = MAX(dp[i-1][j], dp[i][j-1]) + matrix[i][j];
            }
        }
    }

    int max = dp[m-1][n-1];

    // Calculate maximum path sum for reaching (i, j) from bottom-right to top-left
    for (int i = m-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            if (i == m-1 && j == n-1) {
                continue;
            } else if (i == m-1) {
                dp[i][j] = dp[i][j+1] + matrix[i][j];
            } else if (j == n-1) {
                dp[i][j] = dp[i+1][j] + matrix[i][j];
            } else {
                dp[i][j] = MAX(dp[i+1][j], dp[i][j+1]) + matrix[i][j];
            }
        }
    }

    // Find the maximum sum of two paths
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            max = MAX(max, dp[i][j] + dp[m-1-i][n-1-j]);
        }
    }

    printf("%d\n", max);

    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
        free(dp[i]);
    }
    free(matrix);
    free(dp);

    return 0;
}