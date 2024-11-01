#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    // 定义动态规划数组，dp[i][j][a] 表示从 (0,0) 到 (i,j) 且最后一步由 a 吸收时，a 的魔瓶中的魔液量为 a 的方法数
    int dp[801][801][31] = {0};
    dp[0][0][0] = 1;

    // 定义输入矩阵
    int matrix[801][801];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 动态规划填表
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int a = 0; a <= k; a++) {
                if (i > 0) {
                    int new_a = (a - matrix[i-1][j] + k) % k;
                    dp[i][j][a] = (dp[i][j][a] + dp[i-1][j][new_a]) % MOD;
                }
                if (j > 0) {
                    int new_a = (a - matrix[i][j-1] + k) % k;
                    dp[i][j][a] = (dp[i][j][a] + dp[i][j-1][new_a]) % MOD;
                }
            }
        }
    }

    // 计算最终结果
    int result = 0;
    for (int a = 0; a <= k; a++) {
        result = (result + dp[n-1][m-1][a]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}