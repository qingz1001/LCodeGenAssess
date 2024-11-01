#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll n, a, b;
ll h[MAXN];

int main() {
    scanf("%lld %lld %lld", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &h[i]);
    }

    ll g = gcd(a, b);
    for (int i = 0; i < n; i++) {
        if (h[i] % g != 0) {
            printf("-1\n");
            return 0;
        }
    }

    ll min_operations = 0;
    for (int i = 0; i < n; i++) {
        h[i] /= g;
    }

    ll min_a = LLONG_MAX, min_b = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ll x = h[i] / b;
        ll y = (h[i] % b) / a;
        ll z = h[i] - x * b - y * a;
        if (z % g != 0) {
            printf("-1\n");
            return 0;
        }
        min_operations += x + y + z / g;
    }

    printf("%lld\n", min_operations);
    return 0;
}