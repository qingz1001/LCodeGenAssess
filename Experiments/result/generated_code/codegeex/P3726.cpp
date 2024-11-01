#include <stdio.h>
#include <string.h>

typedef long long ll;
ll a, b;
int k;
ll mod;

ll quick_pow(ll x, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

void init() {
    mod = quick_pow(10, k);
}

void solve() {
    ll ans = 0;
    ll x = quick_pow(2, a);
    ll y = quick_pow(2, b);
    ll z = quick_pow(2, a - b);
    ll c = (x - z) % mod;
    ll d = (x - 1) % mod;
    ll e = (y - 1) % mod;
    ll f = (c * e - c * d + d * e) % mod;
    ans = (f * quick_pow(c, mod - 2) % mod) % mod;
    while (ans < 0) ans += mod;
    while (ans >= mod) ans -= mod;
    char res[20];
    sprintf(res, "%lld", ans);
    int len = strlen(res);
    for (int i = 0; i < k - len; i++) {
        printf("0");
    }
    printf("%s\n", res);
}

int main() {
    while (scanf("%lld%lld%d", &a, &b, &k) != EOF) {
        init();
        solve();
    }
    return 0;
}