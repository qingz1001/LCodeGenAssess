#include <stdio.h>
#include <string.h>

#define MOD 1024523

int n, m;
char up[501], down[501];
int dp[501][501][2][2];

int main() {
    // 读取输入
    scanf("%d%d", &n, &m);
    scanf("%s%s", up, down);

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;

    // 动态规划计算
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // 计算从上管道取珠
            if (i > 0) {
                dp[i][j][0][0] = (dp[i][j][0][0] + dp[i-1][j][0][0]) % MOD;
                dp[i][j][0][1] = (dp[i][j][0][1] + dp[i-1][j][0][1]) % MOD;
            }
            // 计算从下管道取珠
            if (j > 0) {
                dp[i][j][1][0] = (dp[i][j][1][0] + dp[i][j-1][1][0]) % MOD;
                dp[i][j][1][1] = (dp[i][j][1][1] + dp[i][j-1][1][1]) % MOD;
            }
            // 计算同时从上下管道取珠
            if (i > 0 && j > 0) {
                if (up[i-1] == down[j-1]) {
                    dp[i][j][0][1] = (dp[i][j][0][1] + dp[i-1][j-1][1][1]) % MOD;
                    dp[i][j][1][0] = (dp[i][j][1][0] + dp[i-1][j-1][0][0]) % MOD;
                } else {
                    dp[i][j][0][0] = (dp[i][j][0][0] + dp[i-1][j-1][1][1]) % MOD;
                    dp[i][j][1][1] = (dp[i][j][1][1] + dp[i-1][j-1][0][0]) % MOD;
                }
            }
        }
    }

    // 计算结果
    int result = (dp[n][m][0][0] + dp[n][m][0][1] + dp[n][m][1][0] + dp[n][m][1][1]) % MOD;
    printf("%d\n", result);

    return 0;
}