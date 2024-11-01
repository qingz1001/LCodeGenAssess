#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int n, m, c, q;
char grid[2][105];
int dp[105][1<<12];

int main() {
    scanf("%d%d%d%d", &n, &m, &c, &q);
    for (int i = 0; i < q; ++i) {
        scanf("%s", grid[0]);
        scanf("%s", grid[1]);
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < (1 << m); ++k) {
                for (int l = 0; l < m; ++l) {
                    if ((k & (1 << l)) == 0) {
                        int next_k = k | (1 << l);
                        if (grid[0][l] == 'W' || (grid[0][l] == 'X' && grid[1][l] == 'W')) {
                            dp[j+1][next_k] = (dp[j+1][next_k] + dp[j][k]) % MOD;
                        }
                        if (grid[0][l] == 'B' || (grid[0][l] == 'X' && grid[1][l] == 'B')) {
                            dp[j+1][next_k] = (dp[j+1][next_k] + dp[j][k]) % MOD;
                        }
                        if (grid[0][l] == 'X' && grid[1][l] == 'X') {
                            dp[j+1][next_k] = (dp[j+1][next_k] + dp[j][k]) % MOD;
                        }
                    }
                }
            }
        }
        int result = 0;
        for (int k = 0; k < (1 << m); ++k) {
            result = (result + dp[n][k]) % MOD;
        }
        printf("%d\n", result);
    }
    return 0;
}