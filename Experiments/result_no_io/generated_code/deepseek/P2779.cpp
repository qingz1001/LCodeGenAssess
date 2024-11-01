#include <stdio.h>
#include <string.h>

#define MOD 1000000009

int main() {
    char sequence[500001];
    scanf("%s", sequence);
    int n = strlen(sequence);

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        if (sequence[i - 1] == '?') {
            dp[i] = (dp[i - 1] * 2) % MOD;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}