#include <stdio.h>
#include <string.h>

#define MAX_N 54
#define MOD 1000000007

long long dp[MAX_N][MAX_N];
long long fac[MAX_N];
long long inv[MAX_N];

long long quick_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void init(int n, int p) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i-1] * i % p;
    }
    inv[n] = quick_pow(fac[n], p-2, p);
    for (int i = n-1; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % p;
    }
}

long long C(int n, int k, int p) {
    if (k > n) return 0;
    return fac[n] * inv[k] % p * inv[n-k] % p;
}

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    
    init(n, p);
    
    memset(dp, 0, sizeof(dp));
    dp[1][1] = m;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= j; k++) {
                long long tmp = dp[i-1][k] * C(j-1, k-1, p) % p * quick_pow(m, (j-k)*(j-k+1)/2, p) % p;
                dp[i][j] = (dp[i][j] + tmp) % p;
            }
        }
    }
    
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + dp[n][i]) % p;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}