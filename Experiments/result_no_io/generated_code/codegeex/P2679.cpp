#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    char a[1001], b[201];
    scanf("%s%s", a, b);

    long long dp[1001][201][51]; // dp[i][j][t] 表示在字符串 A 的前 i 个字符中取 t 个子串匹配到 B 的前 j 个字符的方案数

    // 初始化
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j][0] = 1; // 取 0 个子串时，所有情况都为 1
        }
    }

    // 动态规划
    for (int t = 1; t <= k; t++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 不取新的子串
                dp[i][j][t] = dp[i-1][j][t];

                // 取新的子串
                if (a[i-1] == b[j-1]) {
                    for (int x = 0; x < i; x++) {
                        dp[i][j][t] = (dp[i][j][t] + dp[x][j-1][t-1]) % MOD;
                    }
                }
            }
        }
    }

    printf("%lld\n", dp[n][m][k]);
    return 0;
}