#include <stdio.h>

#define ll long long

ll n, k, p;
ll f[70], inv[70], pw[70];

ll mod(ll x) {
    return x >= p ? x - p : x;
}

ll powM(ll x, ll y) {
    ll res = 1;
    for (; y; y >>= 1) {
        if (y & 1) res = res * x % p;
        x = x * x % p;
    }
    return res;
}

void solve() {
    scanf("%lld%lld%lld", &n, &k, &p);
    ll i, j, l, res, ans = 0;

    for (i = 0; i <= 65; i++) {
        f[i] = inv[i] = pw[i] = 0;
    }

    f[0] = 1;
    for (i = 1; i <= 65; i++) {
        f[i] = mod(f[i - 1] + f[i - 2]);
    }

    inv[1] = 1;
    for (i = 2; i <= 65; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }

    pw[0] = 1;
    for (i = 1; i <= 65; i++) {
        pw[i] = pw[i - 1] * k % p;
    }

    for (i = 0; i <= 65; i++) {
        res = 0;
        for (j = 0; j <= i; j++) {
            l = mod(pw[i - j] * f[j]);
            l = l * (pw[j] + pw[j + 1]) % p;
            res = mod(res + l);
        }
        res = res * inv[i] % p;
        res = res * (i % 2 ? p - 1 : 1) % p;
        ans = mod(ans + res);
    }

    ans = ans * powM(k, n) % p;
    ans = ans - n + 1;
    ans = (ans % p + p) % p;
    printf("%lld\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}