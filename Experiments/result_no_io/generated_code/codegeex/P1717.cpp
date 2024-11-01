#include <stdio.h>
#include <string.h>

int n, h, f[26], d[26], t[25], dp[26][17];

int main() {
    // 输入数据
    scanf("%d%d", &n, &h);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i < n; i++) {
        scanf("%d", &t[i]);
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));

    // 动态规划计算最大钓鱼数量
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = (dp[i][j] > dp[i-1][j-k] + f[i] + (k-1)*d[i]) ? dp[i][j] : dp[i-1][j-k] + f[i] + (k-1)*d[i];
            }
        }
    }

    // 输出最大钓鱼数量
    printf("%d\n", dp[n][h]);
    return 0;
}