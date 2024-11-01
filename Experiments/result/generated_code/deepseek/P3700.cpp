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
    ll factor = x / (a * b / g);
    for (ll i = 1; i <= g; ++i) {
        f[i] = factor * i;
    }
}

ll query(ll k) {
    ll result = 0;
    for (ll i = 1; i <= k; ++i) {
        result = (result + f[i] * i % MOD) % MOD;
    }
    return result;
}

int main() {
    ll m, n;
    scanf("%lld %lld", &m, &n);

    for (ll i = 1; i <= n; ++i) {
        f[i] = i;
    }

    for (ll i = 0; i < m; ++i) {
        ll a, b, x, k;
        scanf("%lld %lld %lld %lld", &a, &b, &x, &k);
        update(a, b, x);
        printf("%lld\n", query(k));
    }

    return 0;
}