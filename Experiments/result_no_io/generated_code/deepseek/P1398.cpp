#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150
#define MAXM 500

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][3][3][3]; // dp[i][j][k][l][m]: i行j列，N的第k部分，O的第l部分，I的第m部分

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
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    for (int m = 0; m < 3; m++) {
                        dp[i][j][k][l][m] = INT_MIN;
                    }
                }
            }
        }
    }

    int ans = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // N 的初始化
            if (i >= 2 && j >= 2) {
                dp[i][j][0][0][0] = grid[i][j] + grid[i-1][j] + grid[i-2][j];
            }

            // O 的初始化
            if (i >= 2 && j >= 2) {
                dp[i][j][1][1][1] = grid[i][j] + grid[i-1][j] + grid[i-2][j] + grid[i][j-1] + grid[i-1][j-1] + grid[i-2][j-1] + grid[i][j-2] + grid[i-1][j-2] + grid[i-2][j-2];
            }

            // I 的初始化
            if (i >= 2 && j >= 2) {
                dp[i][j][2][2][2] = grid[i][j] + grid[i-1][j] + grid[i-2][j];
            }

            // 状态转移
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    for (int m = 0; m < 3; m++) {
                        if (dp[i][j][k][l][m] != INT_MIN) {
                            if (i + 1 < n) {
                                dp[i+1][j][k][l][m] = max(dp[i+1][j][k][l][m], dp[i][j][k][l][m] + grid[i+1][j]);
                            }
                            if (j + 1 < m) {
                                dp[i][j+1][k][l][m] = max(dp[i][j+1][k][l][m], dp[i][j][k][l][m] + grid[i][j+1]);
                            }
                        }
                    }
                }
            }

            // 更新答案
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    for (int m = 0; m < 3; m++) {
                        ans = max(ans, dp[i][j][k][l][m]);
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}