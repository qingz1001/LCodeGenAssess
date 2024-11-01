#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 30005

long long fast_pow(long long base, int exp) {
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

long long fac[MAXN], ifac[MAXN];
long long dp[MAXN], sum[MAXN];
int a[MAXN];

void init(int n) {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i-1] * i % MOD;
        ifac[i] = inv(fac[i]);
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n-k] % MOD;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int s = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s += a[i];
    }
    
    init(s);
    
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = s - 1; j >= a[i]; j--) {
            dp[j] = (dp[j] + dp[j - a[i]] * C(j, a[i])) % MOD;
        }
    }
    
    long long ans = 0;
    for (int i = 0; i <= s - n; i++) {
        sum[i] = dp[s - n - i] * C(s - 1 - i, n - 1) % MOD;
        if (i) sum[i] = (sum[i] + sum[i-1]) % MOD;
    }
    
    for (int i = 1; i <= n - 1; i++) {
        long long tmp = C(n - 2, i - 1) * fac[i] % MOD * fac[n - 1 - i] % MOD;
        tmp = tmp * fast_pow(i, m * i) % MOD * fast_pow(n - 1 - i, m * (n - 1 - i)) % MOD;
        tmp = tmp * (sum[s - n] - (i < s - n ? sum[i - 1] : 0) + MOD) % MOD;
        ans = (ans + tmp * (fast_pow(i, m) + fast_pow(n - 1 - i, m))) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}