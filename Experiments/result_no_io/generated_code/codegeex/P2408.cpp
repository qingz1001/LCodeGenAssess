#include <stdio.h>
#include <string.h>

typedef long long ll;

ll power(ll x, ll y, ll mod) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll inv(ll a, ll p) {
    return power(a, p - 2, p);
}

ll calc_hash(char *s, ll len, ll p, ll mod, ll base) {
    ll res = 0;
    for (ll i = 0; i < len; i++) {
        res = (res * base + (s[i] - 'a' + 1)) % mod;
    }
    return res;
}

int main() {
    ll n;
    scanf("%lld", &n);
    char s[n + 1];
    scanf("%s", s);

    ll p = 131, mod = 1e9 + 7, base = 1;
    ll hash[n + 1], power[n + 1];
    hash[0] = 0;
    power[0] = 1;

    for (ll i = 1; i <= n; i++) {
        power[i] = power[i - 1] * base % mod;
        hash[i] = (hash[i - 1] * base + (s[i - 1] - 'a' + 1)) % mod;
    }

    ll cnt = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = i; j <= n; j++) {
            ll len = j - i + 1;
            ll h = (hash[j] - hash[i - 1] * power[len] % mod + mod) % mod;
            cnt++;
        }
    }

    printf("%lld\n", cnt);
    return 0;
}