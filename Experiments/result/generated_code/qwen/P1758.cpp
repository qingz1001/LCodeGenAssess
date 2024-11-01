#include <stdio.h>
#include <string.h>

#define MOD 1024523

int main() {
    int n, m;
    char upper[501], lower[501];
    scanf("%d %d", &n, &m);
    scanf("%s", upper);
    scanf("%s", lower);

    int dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            result = (result + dp[i][j] * dp[i][j]) % MOD;
        }
    }

    printf("%d\n", result);
    return 0;
}