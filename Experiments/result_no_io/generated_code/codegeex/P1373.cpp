#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int n, m, k;
int dp[805][805][30][2];
int matrix[805][805];

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    dp[1][1][matrix[1][1] % (k + 1)][0] = 1;

    // 动态规划
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int l = 0; l <= k; l++) {
                if (dp[i][j][l][0] > 0) {
                    // 向下走
                    if (i + 1 <= n) {
                        dp[i + 1][j][(l + matrix[i + 1][j]) % (k + 1)][1] = (dp[i + 1][j][(l + matrix[i + 1][j]) % (k + 1)][1] + dp[i][j][l][0]) % MOD;
                    }
                    // 向右走
                    if (j + 1 <= m) {
                        dp[i][j + 1][(l + matrix[i][j + 1]) % (k + 1)][1] = (dp[i][j + 1][(l + matrix[i][j + 1]) % (k + 1)][1] + dp[i][j][l][0]) % MOD;
                    }
                }
                if (dp[i][j][l][1] > 0) {
                    // 向下走
                    if (i + 1 <= n) {
                        dp[i + 1][j][(l + matrix[i + 1][j]) % (k + 1)][0] = (dp[i + 1][j][(l + matrix[i + 1][j]) % (k + 1)][0] + dp[i][j][l][1]) % MOD;
                    }
                    // 向右走
                    if (j + 1 <= m) {
                        dp[i][j + 1][(l + matrix[i][j + 1]) % (k + 1)][0] = (dp[i][j + 1][(l + matrix[i][j + 1]) % (k + 1)][0] + dp[i][j][l][1]) % MOD;
                    }
                }
            }
        }
    }

    // 计算最终结果
    int result = 0;
    for (int l = 0; l <= k; l++) {
        result = (result + dp[n][m][l][1]) % MOD;
    }

    // 输出结果
    printf("%d\n", result);

    return 0;
}