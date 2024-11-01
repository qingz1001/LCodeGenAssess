#include <stdio.h>
#include <string.h>

#define MOD 19901013
#define MAXN 16

int n, m;
char grid[MAXN][MAXN];
int dp[1 << 15][1 << 15];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    dp[0][0] = 1;

    for (int mask1 = 0; mask1 < (1 << m); mask1++) {
        for (int mask2 = 0; mask2 < (1 << m); mask2++) {
            if (dp[mask1][mask2] == 0) continue;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (grid[i][j] == 'x') continue;

                    int new_mask1, new_mask2;
                    new_mask1 = mask1;
                    new_mask2 = mask2;

                    // Place a vertical domino
                    if (j + 1 < m && grid[i][j + 1] == '.') {
                        new_mask1 = (mask1 & ~(1 << j)) & ~(1 << (j + 1));
                    }

                    // Place a horizontal domino
                    if (i + 1 < n && grid[i + 1][j] == '.') {
                        new_mask2 = (mask2 & ~(1 << j)) & ~(1 << (j + 1));
                    }

                    dp[new_mask1][new_mask2] = (dp[new_mask1][new_mask2] + dp[mask1][mask2]) % MOD;
                }
            }
        }
    }

    printf("%d\n", dp[(1 << m) - 1][(1 << m) - 1]);
    return 0;
}