#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define MAXM 7

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][1 << (MAXM * MAXN)];

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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << (m * n)); mask++) {
                dp[i][j][mask] = -1e9;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j][1 << (i * m + j)] = grid[i][j];
        }
    }

    for (int k = 1; k <= 4; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int mask = 0; mask < (1 << (m * n)); mask++) {
                    if ((mask >> (i * m + j)) & 1) continue;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (di == 0 && dj == 0) continue;
                            int ni = i + di, nj = j + dj;
                            if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                                dp[ni][nj][mask | (1 << (i * m + j))] = max(dp[ni][nj][mask | (1 << (i * m + j))], dp[i][j][mask] + grid[ni][nj]);
                            }
                        }
                    }
                }
            }
        }
    }

    int result = -1e9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask = 0; mask < (1 << (m * n)); mask++) {
                if (__builtin_popcount(mask) == 5) {
                    result = max(result, dp[i][j][mask]);
                }
            }
        }
    }

    printf("%d\n", result);

    return 0;
}