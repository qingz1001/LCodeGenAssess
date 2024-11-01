#include <stdio.h>
#include <string.h>

#define MOD 19901013
#define MAXN 15

int n, m;
char grid[MAXN][MAXN];
int dp[MAXN][1 << MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << m); mask++) {
                if (dp[i][mask] == 0) continue;

                int new_mask = mask & ~(1 << j);
                if (grid[i][j] == 'x') {
                    if (j == m - 1) {
                        dp[i + 1][new_mask] = (dp[i + 1][new_mask] + dp[i][mask]) % MOD;
                    } else {
                        dp[i][new_mask] = (dp[i][new_mask] + dp[i][mask]) % MOD;
                    }
                    continue;
                }

                if (j < m - 1 && !(mask & (1 << j)) && !(mask & (1 << (j + 1))) && grid[i][j + 1] == '.') {
                    int next_mask = new_mask | (1 << (j + 1));
                    if (j == m - 2) {
                        dp[i + 1][next_mask] = (dp[i + 1][next_mask] + dp[i][mask]) % MOD;
                    } else {
                        dp[i][next_mask] = (dp[i][next_mask] + dp[i][mask]) % MOD;
                    }
                }

                if (i < n - 1 && !(mask & (1 << j)) && grid[i + 1][j] == '.') {
                    int next_mask = new_mask | (1 << j);
                    if (j == m - 1) {
                        dp[i + 1][next_mask] = (dp[i + 1][next_mask] + dp[i][mask]) % MOD;
                    } else {
                        dp[i][next_mask] = (dp[i][next_mask] + dp[i][mask]) % MOD;
                    }
                }

                if (j == m - 1) {
                    dp[i + 1][new_mask] = (dp[i + 1][new_mask] + dp[i][mask]) % MOD;
                } else {
                    dp[i][new_mask] = (dp[i][new_mask] + dp[i][mask]) % MOD;
                }
            }
        }
    }

    printf("%d\n", dp[n][0]);
    return 0;
}