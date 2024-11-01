#include <stdio.h>
#include <string.h>

typedef long long ll;
ll a, b;
int k;
ll mod;

// 快速幂计算 (x^y) % mod
ll power(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

// 计算组合数 C(n, m) % mod
ll combination(ll n, ll m) {
    ll numerator = 1, denominator = 1;
    for (ll i = 0; i < m; ++i) {
        numerator = numerator * (n - i) % mod;
        denominator = denominator * (i + 1) % mod;
    }
    return numerator * power(denominator, mod - 2) % mod;
}

int main() {
    while (scanf("%lld%lld%d", &a, &b, &k) != EOF) {
        mod = 1;
        for (int i = 1; i <= k; ++i) mod = mod * 10;
        
        ll ans = 0;
        for (ll i = b; i <= a; ++i) {
            ll ways = combination(a + b - i, a - i);
            ans = (ans + ways) % mod;
        }
        ll ten_k = power(10, k);
        printf("%lld\n", ans % ten_k);
    }
    return 0;
}