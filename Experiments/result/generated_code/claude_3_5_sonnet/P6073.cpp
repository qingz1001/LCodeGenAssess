#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAX_N 200005
#define MAX_M 25

long long fac[MAX_N], inv[MAX_N], facinv[MAX_N];
long long pow2[MAX_N], pow3[MAX_N];

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fac[i] = fac[i-1] * i % MOD;
    }
    inv[1] = 1;
    for (int i = 2; i < MAX_N; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    facinv[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        facinv[i] = facinv[i-1] * inv[i] % MOD;
    }
    pow2[0] = pow3[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
        pow3[i] = pow3[i-1] * 3 % MOD;
    }
}

long long quick_pow(long long x, long long n) {
    long long res = 1;
    while (n) {
        if (n & 1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}

void solve1() {
    int n, q, m;
    scanf("%d%d", &n, &q);
    while (q--) {
        scanf("%d", &m);
        printf("%lld\n", quick_pow(m, n));
    }
}

void solve2() {
    int q, n, m;
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &n, &m);
        long long ans = 0;
        for (int k = 0; k <= n; k++) {
            long long tmp = quick_pow(k, n) * facinv[k+m+1] % MOD;
            if (k >= m) {
                tmp = tmp * ((k-m) & 1 ? MOD-1 : 1) % MOD * facinv[k-m] % MOD;
            } else {
                tmp = 0;
            }
            ans = (ans + tmp) % MOD;
        }
        printf("%lld\n", ans);
    }
}

void solve4() {
    int q, n, m;
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &n, &m);
        long long ans = 0;
        for (int k = 0; k <= n; k++) {
            long long tmp = quick_pow(k, n+m) * facinv[k] % MOD;
            tmp = tmp * ((k & 1) ? MOD-1 : 1) % MOD * facinv[k] % MOD;
            ans = (ans + tmp) % MOD;
        }
        printf("%lld\n", ans);
    }
}

void solve5() {
    int q, n, m;
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &n, &m);
        long long ans = 0;
        for (int k = 0; k <= m; k++) {
            long long tmp = quick_pow(k+1, m+n+1) * facinv[k+1] % MOD;
            for (int i = 0; i <= m-k; i++) {
                long long term = tmp * fac[2*n+1] % MOD * facinv[i] % MOD * facinv[2*n+1-i] % MOD;
                term = term * ((m-k-i) & 1 ? MOD-1 : 1) % MOD * facinv[m-k-i] % MOD;
                term = term * quick_pow(k+1, MOD-1-i) % MOD;
                ans = (ans + term) % MOD;
            }
        }
        printf("%lld\n", ans);
    }
}

int main() {
    init();
    int op;
    scanf("%d", &op);
    if (op == 1) solve1();
    else if (op == 2 || op == 3) solve2();
    else if (op == 4) solve4();
    else solve5();
    return 0;
}