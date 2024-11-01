#include <stdio.h>
#include <string.h>

#define MOD 100000000

typedef long long ll;

ll n;

// 计算阶乘并对结果取模
ll factorial(ll x) {
    ll result = 1;
    for (ll i = 1; i <= x; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

// 计算逆元
ll modInverse(ll a, ll m) {
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

// 计算组合数C(n, k)
ll combination(ll n, ll k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    ll numerator = factorial(n);
    ll denominator = (factorial(k) * factorial(n - k)) % MOD;
    return (numerator * modInverse(denominator, MOD)) % MOD;
}

int main() {
    scanf("%lld", &n);
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    ll result = 0;
    for (ll i = 0; i <= n / 2; i++) {
        result = (result + combination(n - 1, i)) % MOD;
    }
    printf("%lld\n", result);
    return 0;
}