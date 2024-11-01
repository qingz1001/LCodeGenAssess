#include <stdio.h>

#define MOD 10007

int dp[128][128];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1; // 有i个节点的树，根节点为空树的情况
    }

    // 动态规划计算
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                dp[i][j] = (dp[i][j] + dp[k][j] * dp[i - k - 1][m] % MOD) % MOD;
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[n][m]);

    return 0;
}