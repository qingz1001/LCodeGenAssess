#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10000
#define MAXM 20

int n, m, cost1, cost2;
int map[MAXM][MAXN];
int dp[MAXN][MAXM][6][6]; // dp[x][y][h][c] 表示在 (x, y) 位置，跳跃高度为 h，连跳数为 c 时的最大收益

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    for (int x = 0; x <= n; x++) {
        for (int y = 0; y < m; y++) {
            for (int h = 1; h <= 5; h++) {
                for (int c = 1; c <= 5; c++) {
                    dp[x][y][h][c] = INT_MIN;
                }
            }
        }
    }

    dp[0][0][1][1] = map[0][0];

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int h = 1; h <= 5; h++) {
                for (int c = 1; c <= 5; c++) {
                    if (dp[x][y][h][c] == INT_MIN) continue;

                    // 不跳跃，直接向右移动
                    if (x + 1 < n && map[y][x + 1] != -1) {
                        dp[x + 1][y][h][c] = max(dp[x + 1][y][h][c], dp[x][y][h][c] + map[y][x + 1]);
                    }

                    // 跳跃
                    for (int dh = -h; dh <= h; dh++) {
                        int ny = y + dh;
                        if (ny < 0 || ny >= m || map[ny][x + 1] == -1) continue;

                        if (dh == 0) {
                            // 水平跳跃
                            dp[x + 1][ny][h][c] = max(dp[x + 1][ny][h][c], dp[x][y][h][c] + map[ny][x + 1]);
                        } else {
                            // 垂直跳跃
                            if (c > 1) {
                                dp[x + 1][ny][h][c - 1] = max(dp[x + 1][ny][h][c - 1], dp[x][y][h][c] + map[ny][x + 1]);
                            } else {
                                dp[x + 1][ny][h][c] = max(dp[x + 1][ny][h][c], dp[x][y][h][c] + map[ny][x + 1]);
                            }
                        }
                    }
                }
            }
        }
    }

    int max_score = INT_MIN;
    int min_c = 6, min_h = 6;

    for (int h = 1; h <= 5; h++) {
        for (int c = 1; c <= 5; c++) {
            if (dp[n - 1][m - 1][h][c] > max_score) {
                max_score = dp[n - 1][m - 1][h][c];
                min_c = c;
                min_h = h;
            } else if (dp[n - 1][m - 1][h][c] == max_score) {
                if (c < min_c) {
                    min_c = c;
                    min_h = h;
                } else if (c == min_c && h < min_h) {
                    min_h = h;
                }
            }
        }
    }

    if (max_score == INT_MIN) {
        printf("mission failed\n");
    } else {
        printf("%d %d %d\n", max_score, min_c, min_h);
    }

    return 0;
}