#include <stdio.h>

#define MOD 10007
#define MAXN 128

int dp[MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 初始化边界条件
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // 动态规划填表
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            long long sum = 0;
            for (int k = 0; k <= j - 1; k++) {
                sum += dp[j - 1][k] * dp[i - j][m * k];
                sum %= MOD;
            }
            dp[i][j] = sum;
        }
    }

    // 输出结果
    printf("%d\n", dp[n][n]);

    return 0;
}