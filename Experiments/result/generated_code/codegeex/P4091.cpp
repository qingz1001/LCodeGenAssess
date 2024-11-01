#include <stdio.h>
#include <string.h>

#define MOD 998244353

long long n, s[100005][20], f[100005], fac[100005], inv[100005];

long long fast_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    
    fac[0] = inv[0] = inv[1] = 1;
    for (long long i = 2; i <= n; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    for (long long i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (long long i = 1; i <= n; i++) {
        inv[i] = inv[i - 1] * inv[i] % MOD;
    }
    
    s[0][0] = 1;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= i; j++) {
            s[i][j] = (s[i - 1][j] * j + s[i - 1][j - 1]) % MOD;
        }
    }
    
    for (long long i = 0; i <= n; i++) {
        for (long long j = 0; j <= i; j++) {
            f[i] = (f[i] + s[i][j] * fast_pow(2, j) % MOD * fac[j] % MOD) % MOD;
        }
    }
    
    long long ans = 0;
    for (long long i = 0; i <= n; i++) {
        ans = (ans + f[i] * fast_pow(inv[i], MOD - 2) % MOD) % MOD;
    }
    
    printf("%lld\n", ans);
    return 0;
}