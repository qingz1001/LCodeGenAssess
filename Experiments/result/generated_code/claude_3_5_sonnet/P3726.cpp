#include <stdio.h>
#include <string.h>

#define MOD 1000000000

long long dp[2][100005];

long long powmod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    long long a, b, k;
    while (scanf("%lld %lld %lld", &a, &b, &k) != EOF) {
        memset(dp, 0, sizeof(dp));
        int mod = powmod(10, k, MOD);
        
        dp[0][0] = 1;
        int cur = 0, nxt = 1;
        
        for (long long i = 1; i <= a; i++) {
            for (long long j = 0; j <= b && j <= i; j++) {
                dp[nxt][j] = 0;
                if (j > 0)
                    dp[nxt][j] = (dp[nxt][j] + dp[cur][j-1]) % mod;
                dp[nxt][j] = (dp[nxt][j] + dp[cur][j]) % mod;
            }
            cur ^= 1;
            nxt ^= 1;
        }
        
        long long ans = 0;
        for (long long j = 0; j < b; j++) {
            ans = (ans + dp[cur][j]) % mod;
        }
        
        printf("%0*lld\n", (int)k, ans);
    }
    return 0;
}