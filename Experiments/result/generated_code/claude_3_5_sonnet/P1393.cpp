#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 200005

long long fast_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

long long inv(long long x) {
    return fast_pow(x, MOD - 2);
}

int n, m, s_len;
int s[MAXN];
long long dp[MAXN];
long long power_m[MAXN];

int main() {
    scanf("%d %d %d", &n, &m, &s_len);
    for (int i = 0; i < s_len; i++) {
        scanf("%d", &s[i]);
    }

    power_m[0] = 1;
    for (int i = 1; i <= n; i++) {
        power_m[i] = power_m[i-1] * m % MOD;
    }

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < s_len && j < i; j++) {
            if (s[s_len - 1 - j] == s[s_len - 1]) {
                int k;
                for (k = 1; k <= j; k++) {
                    if (s[s_len - 1 - j + k] != s[s_len - k]) break;
                }
                if (k > j) {
                    dp[i] = (dp[i] + dp[i - j - 1]) % MOD;
                }
            }
        }
        if (i >= s_len) {
            dp[i] = (dp[i] + dp[i - s_len]) % MOD;
        }
    }

    long long result = (power_m[n] - dp[n] + MOD) % MOD;
    result = result * inv(power_m[n]) % MOD;

    printf("%lld\n", result);

    return 0;
}