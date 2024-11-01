#include <stdio.h>

#define MOD 998244353
#define MAXN 200005
#define MAXQ 500005

typedef long long ll;

ll fac[MAXN], inv[MAXN];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = fac[i-1] * i % MOD;
    }
    inv[MAXN-1] = qpow(fac[MAXN-1], MOD-2);
    for (int i = MAXN-2; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % MOD;
    }
}

ll C(int n, int k) {
    if (k > n) return 0;
    return fac[n] * inv[k] % MOD * inv[n-k] % MOD;
}

ll solve1(int n, int m) {
    ll res = 0;
    for (int k = 0; k < m; k++) {
        res = (res + qpow(k, n)) % MOD;
    }
    return res;
}

ll solve2(int n, int m) {
    ll res = 0;
    for (int k = 0; k <= n; k++) {
        ll gk = k < m ? inv[k+m+1] : 0;
        ll hk = k >= m ? (k-m) % 2 ? MOD-inv[k-m] : inv[k-m] : 0;
        res = (res + qpow(k, n) * gk % MOD * hk) % MOD;
    }
    return res;
}

ll solve4(int n, int m) {
    ll res = 0;
    for (int k = 0; k <= n; k++) {
        ll gk = qpow(k, m) * inv[k] % MOD;
        ll hk = (k % 2 ? MOD-1 : 1) * inv[k] % MOD;
        res = (res + qpow(k, n) * gk % MOD * hk) % MOD;
    }
    return res;
}

ll solve5(int n, int m) {
    ll res = 0;
    for (int k = 0; k <= m; k++) {
        ll t1 = qpow(k+1, m+n+1) * inv[k+1] % MOD;
        ll t2 = 0;
        for (int i = 0; i <= m-k; i++) {
            ll tmp = C(2*n+1, i) * qpow(MOD-1, m-k) % MOD * inv[(m-k-i)] % MOD * qpow(qpow(k+1, i), MOD-2) % MOD;
            t2 = (t2 + tmp) % MOD;
        }
        res = (res + t1 * t2) % MOD;
    }
    return res;
}

int main() {
    init();
    int op;
    scanf("%d", &op);
    if (op == 1) {
        int n, q;
        scanf("%d%d", &n, &q);
        while (q--) {
            int m;
            scanf("%d", &m);
            printf("%lld\n", solve1(n, m));
        }
    } else {
        int q;
        scanf("%d", &q);
        while (q--) {
            int n, m;
            scanf("%d%d", &n, &m);
            if (op == 2 || op == 3) printf("%lld\n", solve2(n, m));
            else if (op == 4) printf("%lld\n", solve4(n, m));
            else printf("%lld\n", solve5(n, m));
        }
    }
    return 0;
}