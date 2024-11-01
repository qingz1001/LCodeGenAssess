#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 200
#define MAX_M 200

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    int matrix[MAX_N][MAX_M];
    int dp[MAX_N][MAX_M];

    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Initialize dp array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MIN;
        }
    }

    // Starting point is at the bottom middle of the matrix
    int start_col = n / 2;
    dp[m-1][start_col] = matrix[m-1][start_col];

    // Fill the dp array
    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i+1][j-1] + matrix[i][j]);
            }
            dp[i][j] = max(dp[i][j], dp[i+1][j] + matrix[i][j]);
            if (j < n - 1) {
                dp[i][j] = max(dp[i][j], dp[i+1][j+1] + matrix[i][j]);
            }
        }
    }

    // Find the maximum value in the first row
    int max_energy = INT_MIN;
    for (int j = 0; j < n; j++) {
        max_energy = max(max_energy, dp[0][j]);
    }

    printf("%d\n", max_energy);

    return 0;
}