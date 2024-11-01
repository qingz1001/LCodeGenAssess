#include <stdio.h>
#include <string.h>

#define MOD 1000000009

int main() {
    char s[500001];
    scanf("%s", s);
    int n = strlen(s);

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == 'B' || s[i - 1] == '?') {
            for (int j = 1; j <= i; j++) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
        if (s[i - 1] == 'W' || s[i - 1] == '?') {
            for (int j = 1; j <= i; j++) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}