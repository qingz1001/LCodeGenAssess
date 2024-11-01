#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 4000005

typedef long long ll;

ll f[MAXN];
ll sum[MAXN];

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void update(ll a, ll b, ll x) {
    ll g = gcd(a, b);
    ll delta = x - f[g];
    f[g] = x;
    for (ll i = 1; i <= g; i++) {
        for (ll j = 1; j <= g; j++) {
            if (gcd(i, j) == g) {
                sum[i] = (sum[i] + delta * j % MOD) % MOD;
                sum[j] = (sum[j] + delta * i % MOD) % MOD;
            }
        }
    }
}

ll query(ll k) {
    ll res = 0;
    for (ll i = 1; i <= k; i++) {
        res = (res + sum[i]) % MOD;
    }
    return res;
}

int main() {
    ll m, n;
    scanf("%lld %lld", &m, &n);

    for (ll i = 1; i <= n; i++) {
        f[i] = i;
        sum[i] = i * i % MOD;
    }

    for (ll i = 0; i < m; i++) {
        ll a, b, x, k;
        scanf("%lld %lld %lld %lld", &a, &b, &x, &k);
        update(a, b, x);
        printf("%lld\n", query(k));
    }

    return 0;
}