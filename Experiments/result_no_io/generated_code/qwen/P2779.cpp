#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    char s[500001];
    int n, dp[500001][3], i, j;

    scanf("%s", s);
    n = strlen(s);

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1; // No '?' at the start

    for (i = 0; i < n; i++) {
        if (s[i] == 'B') {
            dp[i+1][0] = (dp[i][0] + dp[i][1]) % MOD;
            dp[i+1][1] = dp[i][2];
        } else if (s[i] == 'W') {
            dp[i+1][1] = (dp[i][0] + dp[i][1]) % MOD;
            dp[i+1][2] = dp[i][2];
        } else {
            dp[i+1][0] = (dp[i][0] * 2) % MOD;
            dp[i+1][1] = (dp[i][1] * 2) % MOD;
            dp[i+1][2] = (dp[i][2] * 2) % MOD;
        }
    }

    printf("%d\n", dp[n][1]);

    return 0;
}