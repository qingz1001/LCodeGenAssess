#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll gcd(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ll solve(ll n, ll k, ll p) {
    if (n == 1) return k % p;
    
    ll g = gcd(n, p - 1);
    ll t = (p - 1) / g;
    ll s = mod_pow(k, n / g, p);
    
    ll result = 0;
    for (ll i = 0; i < g; i++) {
        result = (result + mod_pow(s, i, p)) % p;
    }
    
    return (k * mod_pow(k - 1, n - 1, p) - result + p) % p;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        ll n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);
        printf("%lld\n", solve(n, k, p));
    }
    
    return 0;
}