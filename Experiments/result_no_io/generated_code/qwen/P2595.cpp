#include <stdio.h>
#include <stdlib.h>

#define MOD 19901013

int dp[16][16][16][16];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %c", &grid[i][j]);
        }
    }

    dp[0][0][0][0] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= n - i; ++k) {
                for (int l = 0; l <= m - j; ++l) {
                    if (i > 0 && j > 0 && grid[k][l] == '.' && grid[k + i - 1][l] == '.' && grid[k][l + j - 1] == '.' && grid[k + i - 1][l + j - 1] == '.') {
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][j][k + 1][l]) % MOD;
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i][j - 1][k][l + 1]) % MOD;
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][j - 1][k + 1][l + 1]) % MOD;
                    } else if (i > 0 && grid[k][l] == '.' && grid[k + i - 1][l] == '.') {
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i - 1][j][k + 1][l]) % MOD;
                    } else if (j > 0 && grid[k][l] == '.' && grid[k][l + j - 1] == '.') {
                        dp[i][j][k][l] = (dp[i][j][k][l] + dp[i][j - 1][k][l + 1]) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", dp[n][m][0][0]);

    return 0;
}