#include <stdio.h>

#define MAXN 1001

int triangle[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);

    // 读取输入的数字三角形
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    // 初始化第一行的dp值
    for (int j = 1; j <= n; j++) {
        dp[1][j] = triangle[1][j];
    }

    // 动态规划计算最大路径和
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = triangle[i][j] + (dp[i-1][j-1] > dp[i-1][j] ? dp[i-1][j-1] : dp[i-1][j]);
        }
    }

    // 找出最后一行的最大值
    int max = dp[n][1];
    for (int j = 2; j <= n; j++) {
        if (dp[n][j] > max) {
            max = dp[n][j];
        }
    }

    // 输出结果
    printf("%d\n", max);

    return 0;
}