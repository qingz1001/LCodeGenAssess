#include <stdio.h>
#include <string.h>

#define MOD 10007
#define MAX_N 1000001

long long dp[MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1] + i;
        if (dp[i] >= MOD) dp[i] %= MOD;
    }

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result += dp[i] * (n - i + 1);
        if (result >= MOD) result %= MOD;
    }

    printf("%lld\n", result);

    return 0;
}