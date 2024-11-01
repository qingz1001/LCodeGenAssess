#include <stdio.h>
#include <string.h>

#define MAXN 2000010
#define INF 0x3f3f3f3f

int w[MAXN];
int dp[MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++) {
        scanf("%d", &w[i]);
    }

    // 初始化dp数组为一个很大的值
    memset(dp, INF, sizeof(dp));

    // 每个矩阵单独相乘的代价为0
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    // 枚举区间长度
    for (int len = 2; len <= n; len++) {
        // 枚举起点
        for (int i = 1; i <= n - len + 1; i++) {
            // 计算终点
            int j = i + len - 1;
            // 枚举分割点
            for (int k = i; k < j; k++) {
                dp[i][j] = (dp[i][j] < dp[i][k] + dp[k + 1][j] + w[i] * w[k + 1] * w[j + 1]) ? dp[i][j] : dp[i][k] + dp[k + 1][j] + w[i] * w[k + 1] * w[j + 1];
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}