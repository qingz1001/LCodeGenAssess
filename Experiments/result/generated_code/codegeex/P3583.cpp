#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n;
ll *k;
ll *superheavy;

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void init() {
    k = (ll *)malloc(sizeof(ll) * (n + 1));
    superheavy = (ll *)malloc(sizeof(ll) * (n + 1));
    k[1] = 1;
    superheavy[1] = 1;
    ll max_k = 1;
    for (ll i = 2; i <= n; i++) {
        k[i] = LLONG_MAX;
        for (ll j = 1; j * j <= i; j++) {
            if (k[i - j * j] != LLONG_MAX) {
                k[i] = min(k[i], k[i - j * j] + 1);
            }
        }
        if (k[i] == LLONG_MAX) {
            k[i] = -1;
        }
        if (k[i] > max_k) {
            max_k = k[i];
        }
        if (k[i] < max_k) {
            superheavy[i] = 1;
        } else {
            superheavy[i] = 0;
        }
    }
}

int main() {
    scanf("%lld", &n);
    init();
    ll ans1 = k[n];
    ll ans2 = 0;
    for (ll i = 1; i <= n; i++) {
        ans2 += superheavy[i];
    }
    printf("%lld %lld\n", ans1, ans2);
    return 0;
}