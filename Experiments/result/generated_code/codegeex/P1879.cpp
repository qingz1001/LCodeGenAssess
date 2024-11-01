#include <stdio.h>
#include <string.h>

#define MOD 100000000

int m, n;
int field[13][13];
int dp[13][1 << 13];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &field[i][j]);
        }
    }

    // 初始化第一行的状态
    for (int i = 0; i < (1 << n); i++) {
        bool valid = true;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) && field[1][j+1] == 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            dp[1][i] = 1;
        }
    }

    // 动态规划计算每一行的状态
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = 0; k < (1 << n); k++) {
                bool valid = true;
                for (int l = 0; l < n; l++) {
                    if ((j & (1 << l)) && (k & (1 << l)) && field[i][l+1] == 0) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
                }
            }
        }
    }

    // 计算最终结果
    int result = 0;
    for (int i = 0; i < (1 << n); i++) {
        result = (result + dp[m][i]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}