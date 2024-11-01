#include <stdio.h>

#define MAX_M 11
#define MAX_N 21

long long dp[MAX_M][MAX_N];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // 初始化第一行和第一列
    for (int i = 0; i < m; i++) {
        dp[i][0] = 1;
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = 1;
    }

    // 动态规划填表
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    // 输出结果
    printf("%lld\n", dp[m-1][n-1]);

    return 0;
}