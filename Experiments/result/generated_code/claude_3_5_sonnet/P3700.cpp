#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 4000005

typedef long long ll;

ll f[MAXN];
ll inv[MAXN];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i <= n; i++)
        f[i] = i;
}

void modify(int a, int b, ll x) {
    ll t = x * inv[a] % MOD * inv[b] % MOD;
    for (int i = 1; i <= b; i++)
        f[i] = f[i] * qpow(f[a], MOD - 2) % MOD * t % MOD * a % MOD;
    for (int i = b + 1; i <= a; i++)
        f[i] = f[i] * qpow(f[a], MOD - 2) % MOD * t % MOD * a % MOD * i % MOD * inv[b] % MOD;
    f[a] = t * a % MOD * b % MOD;
}

ll query(int k) {
    ll res = 0;
    for (int i = 1; i <= k; i++)
        res = (res + f[i] * i % MOD) % MOD;
    return res * k % MOD;
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);
    init(n);
    
    while (m--) {
        int a, b, k;
        ll x;
        scanf("%d%d%lld%d", &a, &b, &x, &k);
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        modify(a, b, x);
        printf("%lld\n", query(k));
    }
    
    return 0;
}