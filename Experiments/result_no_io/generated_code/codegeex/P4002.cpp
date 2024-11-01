#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <vector>

#define inf 0x3f3f3f3f
#define maxn 30005
#define maxm 1005
#define mod 998244353

using namespace std;

typedef long long ll;

ll n, m, a[maxn], ans, s, fac[maxn], inv[maxn], invfac[maxn];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = inv[1] = invfac[0] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
        invfac[i] = invfac[i - 1] * inv[i] % mod;
    }
}

ll C(ll n, ll m) {
    if (n < m) return 0;
    return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll A(ll n, ll m) {
    return qpow(C(n + m - 1, m), m);
}

ll solve(ll x) {
    ll res = 0;
    for (int i = 1; i <= x; i++) {
        res = (res + qpow(i, m) * A(x, i)) % mod;
    }
    return res;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        s += a[i];
    }
    init();
    for (int i = 1; i <= n; i++) {
        ans = (ans + solve(a[i]) * qpow(s - a[i], n - 1) % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}