#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    long long *dp = (long long *)calloc(n + 1, sizeof(long long));
    dp[0] = 1;
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = (dp[i] + dp[j]) % MOD;
        }
        ans = (ans + dp[i]) % MOD;
    }

    printf("%lld\n", ans);
    free(a);
    free(dp);
    return 0;
}