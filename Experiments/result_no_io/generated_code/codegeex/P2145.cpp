#include <stdio.h>
#include <string.h>

int a[505], dp[505][505], n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            if (a[i] == a[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            }
            for (int k = i; k < j; k++) {
                dp[i][j] = dp[i][j] < dp[i][k] + dp[k + 1][j] ? dp[i][j] : dp[i][k] + dp[k + 1][j];
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}