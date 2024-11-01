#include <stdio.h>

#define MOD 100000000

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

ll fib(ll n) {
    if (n <= 1) return n;
    ll a = 0, b = 1, c;
    for (ll i = 2; i <= n; ++i) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll g = gcd(n, m);
    printf("%lld\n", fib(g));
    return 0;
}