#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 21
#define INF 0x3f3f3f3f

int n, m, cost1, cost2;
int grid[MAXM][MAXN];
int dp[MAXN][MAXM];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = -INF;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    int max_height = 0;
    for (int i = 1; i <= m; ++i) {
        if (grid[i][1] != -1) {
            max_height = i;
            break;
        }
    }

    dp[1][max_height] = grid[max_height][1];
    for (int i = 1; i <= n; ++i) {
        for (int h = 1; h <= m; ++h) {
            if (dp[i][h] == -INF) continue;

            for (int nh = 1; nh <= m; ++nh) {
                if (abs(nh - h) > 1) continue;
                if (grid[nh][i + 1] == -1) continue;
                if (nh == h) {
                    dp[i + 1][nh] = fmax(dp[i + 1][nh], dp[i][h] + grid[nh][i + 1]);
                } else {
                    dp[i + 1][nh] = fmax(dp[i + 1][nh], dp[i][h] + grid[nh][i + 1] - cost1);
                }
            }
        }
    }

    int max_score = -1, min_jumps = INF, min_height = INF;
    for (int h = 1; h <= m; ++h) {
        if (dp[n][h] > max_score) {
            max_score = dp[n][h];
            min_jumps = 1;
            min_height = h;
        } else if (dp[n][h] == max_score && h < min_height) {
            min_height = h;
        } else if (dp[n][h] == max_score && h == min_height && 1 < min_jumps) {
            min_jumps = 1;
        }
    }

    if (max_score == -1) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", max_score, min_jumps, min_height);
    }

    return 0;
}