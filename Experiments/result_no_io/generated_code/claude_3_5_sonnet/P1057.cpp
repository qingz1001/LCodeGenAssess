#include <stdio.h>

#define MAX_N 31
#define MAX_M 31

long long dp[MAX_M][MAX_N];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 初始化
    dp[0][1] = 1;  // 开始时球在小蛮（1号）手中

    // 动态规划
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // 从左边传球
            dp[i][j] += dp[i-1][j == 1 ? n : j-1];
            // 从右边传球
            dp[i][j] += dp[i-1][j == n ? 1 : j+1];
        }
    }

    // 输出结果
    printf("%lld\n", dp[m][1]);

    return 0;
}