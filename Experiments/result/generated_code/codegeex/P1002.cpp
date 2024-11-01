#include <stdio.h>
#include <string.h>

#define MAXN 21

long long dp[MAXN][MAXN];

int main() {
    int n, m, sx, sy;
    scanf("%d%d%d%d", &n, &m, &sx, &sy);

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    // 遍历棋盘的每一个位置
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // 如果当前位置不是马的控制点
            if (!((i == sx || i == sx + 1 || i == sx - 1) && (j == sy || j == sy + 2 || j == sy - 2)) &&
                !((j == sy || j == sy + 1 || j == sy - 1) && (i == sx || i == sx + 2 || i == sx - 2))) {
                // 如果当前位置不是起点
                if (i > 0) dp[i][j] += dp[i - 1][j];
                if (j > 0) dp[i][j] += dp[i][j - 1];
            }
        }
    }

    // 输出结果
    printf("%lld\n", dp[n][m]);

    return 0;
}