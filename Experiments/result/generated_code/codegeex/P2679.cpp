#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char A[1005], B[205];
    scanf("%s %s", A, B);

    int dp[1005][205][55];
    memset(dp, 0, sizeof(dp));

    // 初始化：当 k=1 时，直接匹配 A 和 B
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j][1] = 1;
            } else if (i > 0 && j == 0) {
                dp[i][j][1] = dp[i-1][j][1];
            } else if (i == 0 && j > 0) {
                dp[i][j][1] = 0;
            } else {
                dp[i][j][1] = (dp[i-1][j][1] + (A[i-1] == B[j-1] ? dp[i-1][j-1][1] : 0)) % MOD;
            }
        }
    }

    // 动态规划计算
    for (int kk = 2; kk <= k; kk++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j][kk] = dp[i-1][j][kk]; // 不使用 A[i-1]
                if (A[i-1] == B[j-1]) {
                    dp[i][j][kk] = (dp[i][j][kk] + dp[i-1][j-1][kk-1]) % MOD; // 使用 A[i-1]
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[n][m][k]);

    return 0;
}