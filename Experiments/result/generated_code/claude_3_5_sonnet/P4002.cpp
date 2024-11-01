#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 30005
#define MAXM 31

typedef long long ll;

ll quick_pow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

ll inv[MAXN], fac[MAXN], ifac[MAXN];
ll dp[MAXN][MAXM], sum[MAXN][MAXM];
int a[MAXN];

void init(int n) {
    fac[0] = ifac[0] = inv[1] = 1;
    for (int i = 1; i <= n; i++) {
        if (i > 1) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        fac[i] = fac[i-1] * i % MOD;
        ifac[i] = ifac[i-1] * inv[i] % MOD;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    ll s = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s += a[i];
    }
    
    init(n);
    
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i && j <= m; j++) {
            dp[i][j] = dp[i-1][j-1] * quick_pow(j, m) % MOD * a[i] % MOD;
            sum[i][j] = (sum[i-1][j] + dp[i][j]) % MOD;
        }
    }
    
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll tmp = sum[n][i] * fac[n-2] % MOD * ifac[i-1] % MOD * ifac[n-1-i] % MOD;
        ans = (ans + tmp) % MOD;
    }
    
    ans = ans * quick_pow(s-n, MOD-2) % MOD;
    printf("%lld\n", ans);
    
    return 0;
}