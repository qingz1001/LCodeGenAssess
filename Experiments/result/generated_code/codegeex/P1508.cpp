#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int grid[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int dp[m][n];
    for (int j = 0; j < n; j++) {
        dp[m-1][j] = grid[m-1][j];
    }

    for (int i = m-2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int max_energy = dp[i+1][j];
            if (j > 0) {
                max_energy = (max_energy > dp[i+1][j-1]) ? max_energy : dp[i+1][j-1];
            }
            if (j < n-1) {
                max_energy = (max_energy > dp[i+1][j+1]) ? max_energy : dp[i+1][j+1];
            }
            dp[i][j] = max_energy + grid[i][j];
        }
    }

    int max_energy = dp[0][n/2];
    for (int j = 0; j < n; j++) {
        if (dp[0][j] > max_energy) {
            max_energy = dp[0][j];
        }
    }

    printf("%d\n", max_energy);
    return 0;
}