#include <stdio.h>
#include <string.h>

int n, m, a[300][300], dp[300][300][2], ans;
const int MOD = 10007;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            scanf(" %c", &ch);
            if (ch == '1') a[i][j] = 1;
            else a[i][j] = -1;
        }
    }

    dp[1][1][a[1][1]] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] != -1) {
                dp[i][j][a[i][j]] = (dp[i][j][a[i][j]] + dp[i][j][1 - a[i][j]]) % MOD;
                dp[i][j][1 - a[i][j]] = 0;
            } else {
                dp[i][j][0] = (dp[i][j - 1][1] + dp[i - 1][j][1] + dp[i][j - 1][0] + dp[i - 1][j][0]) % MOD;
                dp[i][j][1] = (dp[i][j - 1][0] + dp[i - 1][j][0] + dp[i][j - 1][1] + dp[i - 1][j][1]) % MOD;
            }
        }
    }

    ans = (dp[n][m][0] + dp[n][m][1]) % MOD;
    printf("%d\n", ans);
    return 0;
}