#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int main() {
    char s[500005];
    scanf("%s", s);
    int n = strlen(s);
    long long dp[n + 1][2];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = dp[0][1] = 1;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') {
            dp[i + 1][0] = (dp[i][0] + dp[i][1]) % MOD;
        } else if (s[i] == 'W') {
            dp[i + 1][1] = (dp[i][0] + dp[i][1]) % MOD;
        } else {
            dp[i + 1][0] = (dp[i][0] * 2) % MOD;
            dp[i + 1][1] = (dp[i][1] * 2) % MOD;
        }
    }

    printf("%lld\n", (dp[n][0] + dp[n][1]) % MOD);
    return 0;
}