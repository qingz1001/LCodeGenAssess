#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 20
#define INF 1e9

int n, m, cost1, cost2;
int grid[MAXM][MAXN];
int dp[MAXN][MAXM][6];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < MAXM; ++j) {
            for (int k = 0; k <= 5; ++k) {
                dp[i][j][k] = -INF;
            }
        }
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    init();
    dp[0][1][1] = 0;

    for (int i = 0; i < n; ++i) {
        for (int h = 1; h < m; ++h) {
            for (int k = 1; k <= 5; ++k) {
                if (dp[i][h][k] == -INF) continue;
                if (i + h < n && grid[h][i + h] != -1) {
                    dp[i + h][h][k] = max(dp[i + h][h][k], dp[i][h][k] + grid[h][i + h]);
                }
                if (k > 1 && i + 2 * h < n && grid[h][i + 2 * h] != -1) {
                    dp[i + 2 * h][h][k] = max(dp[i + 2 * h][h][k], dp[i][h][k] + grid[h][i + 2 * h]);
                }
            }
        }
    }

    int max_score = -INF;
    int min_jumps = 6;
    int min_height = 6;

    for (int k = 1; k <= 5; ++k) {
        for (int h = 1; h < m; ++h) {
            if (dp[n - 1][h][k] != -INF) {
                if (dp[n - 1][h][k] > max_score) {
                    max_score = dp[n - 1][h][k];
                    min_jumps = k;
                    min_height = h;
                } else if (dp[n - 1][h][k] == max_score) {
                    if (k < min_jumps || (k == min_jumps && h < min_height)) {
                        min_jumps = k;
                        min_height = h;
                    }
                }
            }
        }
    }

    if (max_score == -INF) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", max_score, min_jumps, min_height);
    }

    return 0;
}