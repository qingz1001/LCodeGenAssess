#include <stdio.h>
#include <stdlib.h>

#define ll long long

ll n, p;
ll *z, *a, *b;

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll check(ll mid) {
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        if (mid <= z[i]) {
            sum += a[i] * mid;
        } else {
            sum += a[i] * z[i] + b[i] * (mid - z[i]);
        }
    }
    return sum;
}

int main() {
    scanf("%lld %lld", &n, &p);
    z = (ll*)malloc(n * sizeof(ll));
    a = (ll*)malloc(n * sizeof(ll));
    b = (ll*)malloc(n * sizeof(ll));
    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld %lld", z + i, a + i, b + i);
    }

    ll l = 0, r = 1e10;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (check(mid) >= p) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    printf("%lld\n", l);
    free(z);
    free(a);
    free(b);
    return 0;
}