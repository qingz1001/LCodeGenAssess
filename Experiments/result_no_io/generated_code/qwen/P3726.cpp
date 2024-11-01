#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000000

long long binomial_coefficient(long long n, long long k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long *dp = (long long *)malloc((k + 1) * sizeof(long long));
    for (int i = 0; i <= k; i++) dp[i] = 0;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = k; j >= 0; j--) {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }
    long long result = dp[k];
    free(dp);
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b, k;
        scanf("%lld %lld %lld", &a, &b, &k);
        long long count = 0;
        for (long long i = b + 1; i <= a; i++) {
            count = (count + binomial_coefficient(a, i)) % MOD;
        }
        printf("%0*d\n", k, count);
    }
    return 0;
}