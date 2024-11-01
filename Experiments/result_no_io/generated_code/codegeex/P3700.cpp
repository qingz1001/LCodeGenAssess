#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void exgcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    ll temp = *x;
    *x = *y;
    *y = temp - (a / b) * (*y);
}

ll inv(ll a) {
    ll x, y;
    exgcd(a, MOD, &x, &y);
    return (x % MOD + MOD) % MOD;
}

ll f(ll a, ll b) {
    ll g = gcd(a, b);
    return a / g * b / g * inv((a / g + b / g) % MOD) % MOD;
}

ll sum(ll n) {
    return n * (n + 1) / 2 % MOD;
}

ll calc(ll n, ll m) {
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            ans = (ans + i * j % MOD * f(i, j) % MOD) % MOD;
        }
    }
    return ans;
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);
    ll a, b, x, k, ans = 0;
    while (m--) {
        scanf("%lld%lld%lld%lld", &a, &b, &x, &k);
        ll g = gcd(a, b);
        ll p = a / g;
        ll q = b / g;
        ll invpq = inv(p * q % MOD);
        ll factor = x * invpq % MOD;
        ans = (ans + (sum(k) - sum(k - p) - sum(k - q) + sum(k - p - q)) % MOD * factor % MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}