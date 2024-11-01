#include <stdio.h>
#include <string.h>
#include <algorithm>
#define ll long long
#define mod 998244353
using namespace std;

ll n, m, s, l, n1, m1, k1, invn, invm, C[200005][200005], P[200005], fac[200005], inv[200005];

ll qpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

void pre() {
    C[0][0] = fac[0] = inv[0] = inv[1] = 1;
    for (int i = 1; i <= 200000; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for (int i = 2; i <= 200000; i++) inv[i] = inv[i] * inv[i - 1] % mod;
    for (int i = 1; i <= 200000; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 0; i <= 200000; i++) P[i] = qpow(i, l);
}

int main() {
    scanf("%lld%lld%lld%lld", &n, &m, &s, &l);
    pre();
    while (s--) {
        scanf("%lld%lld%lld", &n1, &m1, &k1);
        if (n1 == k1) {
            printf("0\n");
            continue;
        }
        invn = qpow(n1, mod - 2);
        invm = qpow(m1, mod - 2);
        ll ans = 0;
        for (int i = 0; i <= k1; i++) {
            ll t = (C[n1][i] * C[m1][i] % mod * C[n1 - m1][k1 - i] % mod * P[i] % mod) * invn % mod * invm % mod;
            if ((k1 - i) & 1) ans = (ans - t + mod) % mod;
            else ans = (ans + t) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}