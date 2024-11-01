#include <stdio.h>
#define MOD 998244353

int main() {
    int n;
    scanf("%d", &n);
    int a[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    long long ans = 0;
    long long dp[n+1] = {0};

    for (int i = 1; i <= n; i++) {
        dp[i] = 2 * dp[i-1] + 1;
        if (dp[i] >= MOD) dp[i] -= MOD;
        for (int j = 1; j < i; j++) {
            if (a[j] != a[i]) {
                dp[i] = (dp[i] - dp[j-1] + MOD) % MOD;
            }
        }
        ans = (ans + dp[i]) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}