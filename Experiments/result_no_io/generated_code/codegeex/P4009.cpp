#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 101

int n, k, a, b, c;
int map[MAXN][MAXN];
int dp[MAXN][MAXN][11];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    // 读取输入
    scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    // 初始化dp数组，设置为一个较大的值
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int t = 0; t <= k; t++) {
                dp[i][j][t] = INT_MAX;
            }
        }
    }

    // 起点的初始状态
    dp[1][1][k] = 0;

    // 动态规划求解
    for (int t = k; t >= 1; t--) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 向下移动
                if (i + 1 <= n) {
                    dp[i + 1][j][t - 1] = min(dp[i + 1][j][t - 1], dp[i][j][t] + (i > j ? b : 0));
                    if (map[i + 1][j]) {
                        dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][t] + a + (i > j ? b : 0));
                    }
                }
                // 向右移动
                if (j + 1 <= n) {
                    dp[i][j + 1][t - 1] = min(dp[i][j + 1][t - 1], dp[i][j][t] + (i > j ? b : 0));
                    if (map[i][j + 1]) {
                        dp[i][j + 1][k] = min(dp[i][j + 1][k], dp[i][j][t] + a + (i > j ? b : 0));
                    }
                }
                // 增设油库
                if (i < n) {
                    dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][t] + c + a + (i > j ? b : 0));
                }
                if (j < n) {
                    dp[i][j + 1][k] = min(dp[i][j + 1][k], dp[i][j][t] + c + a + (i > j ? b : 0));
                }
            }
        }
    }

    // 找到最小的费用
    int ans = INT_MAX;
    for (int t = 0; t <= k; t++) {
        ans = min(ans, dp[n][n][t]);
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}