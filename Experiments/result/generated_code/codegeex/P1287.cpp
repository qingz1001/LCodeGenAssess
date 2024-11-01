#include <stdio.h>

int main() {
    int n, r;
    scanf("%d %d", &n, &r);

    // 初始化动态规划数组
    int dp[n + 1][r + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= r; j++) {
            dp[i][j] = 0;
        }
    }

    // 初始化边界条件
    dp[0][0] = 1;

    // 动态规划计算球放入盒子的方案数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r; j++) {
            // 将第i个球放入第j个盒子
            dp[i][j] = dp[i - 1][j - 1];
            // 将第i个球放入之前的盒子中
            for (int k = 1; k < j; k++) {
                dp[i][j] += dp[i - 1][k];
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[n][r]);

    return 0;
}