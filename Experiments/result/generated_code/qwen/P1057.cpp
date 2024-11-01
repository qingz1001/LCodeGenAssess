#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // dp[i][j] 表示从第 i 个人手中传递 j 次球回到第 i 个人手中的方法数
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((m + 1) * sizeof(int));
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    // 初始状态：从第 1 个人手中传递 0 次球回到第 1 个人手中的方法数为 1
    dp[1][0] = 1;

    // 动态规划转移方程：
    // dp[i][j] = dp[i-1][j-1] + dp[i+1][j-1]
    // 注意处理边界情况，即第 n 个人和第 1 个人之间的传递
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = (dp[(i - 1 + n) % n][j - 1] + dp[(i + 1) % n][j - 1]) % MOD;
        }
    }

    // 结果是从第 1 个人手中传递 m 次球回到第 1 个人手中的方法数
    printf("%d\n", dp[1][m]);

    // 释放内存
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}