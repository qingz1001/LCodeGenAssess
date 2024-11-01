#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define MAXM 7
#define INF 0x3f3f3f3f

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][1 << MAXM][1 << MAXM];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(dp, -INF, sizeof(dp));
    dp[0][0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask1 = 0; mask1 < (1 << m); mask1++) {
                for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                    if (dp[i][j][mask1][mask2] == -INF) continue;

                    int ni = i, nj = j + 1;
                    if (nj == m) {
                        ni++;
                        nj = 0;
                    }

                    if (ni < n) {
                        dp[ni][nj][mask1][mask2] = max(dp[ni][nj][mask1][mask2], dp[i][j][mask1][mask2]);
                    }

                    if (i > 0 && !(mask1 & (1 << j)) && !(mask2 & (1 << j))) {
                        dp[i][j][mask1 | (1 << j)][mask2 | (1 << j)] = max(dp[i][j][mask1 | (1 << j)][mask2 | (1 << j)], dp[i][j][mask1][mask2] + grid[i][j]);
                    }

                    if (j > 0 && !(mask1 & (1 << (j - 1))) && !(mask2 & (1 << (j - 1)))) {
                        dp[i][j][mask1 | (1 << (j - 1))][mask2 | (1 << (j - 1))] = max(dp[i][j][mask1 | (1 << (j - 1))][mask2 | (1 << (j - 1))], dp[i][j][mask1][mask2] + grid[i][j]);
                    }
                }
            }
        }
    }

    int ans = -INF;
    for (int mask1 = 0; mask1 < (1 << m); mask1++) {
        for (int mask2 = 0; mask2 < (1 << m); mask2++) {
            ans = max(ans, dp[n - 1][m - 1][mask1][mask2]);
        }
    }

    printf("%d\n", ans);
    return 0;
}