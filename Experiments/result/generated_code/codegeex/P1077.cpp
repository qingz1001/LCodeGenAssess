#include <stdio.h>

#define MOD 1000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[105];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    int dp[105][105];
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i-1][j];
            if (j - 1 <= a[i]) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }

    printf("%d\n", dp[n][m]);
    return 0;
}