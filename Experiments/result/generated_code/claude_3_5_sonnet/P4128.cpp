#include <stdio.h>
#include <string.h>

#define MAX_N 54
#define MOD 1000000007

long long fact[MAX_N];
long long inv[MAX_N];
long long dp[MAX_N][MAX_N];

long long quick_pow(long long x, long long n, long long mod) {
    long long res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

void init(int n, int p) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i % p;
    }
    inv[n] = quick_pow(fact[n], p-2, p);
    for (int i = n-1; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % p;
    }
}

long long C(int n, int m, int p) {
    if (m > n) return 0;
    return fact[n] * inv[m] % p * inv[n-m] % p;
}

int main() {
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    
    init(n, p);
    
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][j] = dp[i-1][j] * (j+1) % p;
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (i-j)) % p;
            }
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long tmp = C(m+i-1, i, p) * dp[n][i] % p * fact[n-1] % p;
        ans = (ans + tmp) % p;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}