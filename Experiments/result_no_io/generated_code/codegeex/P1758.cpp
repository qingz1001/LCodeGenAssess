#include <stdio.h>
#include <string.h>

#define MOD 1024523

char upper[501], lower[501];
int n, m, upperCount[2], lowerCount[2];
int dp[501][501][2][2];

int main() {
    // 读取输入
    scanf("%d%d", &n, &m);
    scanf("%s", upper);
    scanf("%s", lower);

    // 统计上下两个管道中两种球的数量
    for (int i = 0; i < n; i++) {
        upperCount[upper[i] - 'A']++;
    }
    for (int i = 0; i < m; i++) {
        lowerCount[lower[i] - 'A']++;
    }

    // 初始化动态规划数组
    dp[0][0][0][0] = 1;

    // 动态规划计算
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= upperCount[0]; k++) {
                for (int l = 0; l <= lowerCount[0]; l++) {
                    if (dp[i][j][k][l] > 0) {
                        // 从上管道移球
                        if (i < n && k < upperCount[1]) {
                            dp[i + 1][j][k + 1][l] = (dp[i + 1][j][k + 1][l] + dp[i][j][k][l]) % MOD;
                        }
                        // 从下管道移球
                        if (j < m && l < lowerCount[1]) {
                            dp[i][j + 1][k][l + 1] = (dp[i][j + 1][k][l + 1] + dp[i][j][k][l]) % MOD;
                        }
                    }
                }
            }
        }
    }

    // 计算结果
    int result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            result = (result + dp[i][j][upperCount[1]][lowerCount[1]]) % MOD;
        }
    }

    // 输出结果
    printf("%d\n", result);

    return 0;
}