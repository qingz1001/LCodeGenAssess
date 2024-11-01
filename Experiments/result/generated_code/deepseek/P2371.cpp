#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 12
#define MAXA 500000
#define MAXR 1000000000000LL

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll solve(ll n, ll *a, ll l, ll r) {
    ll min_a = a[0];
    for (ll i = 1; i < n; i++) {
        if (a[i] < min_a) {
            min_a = a[i];
        }
    }

    ll *reachable = (ll *)malloc((min_a + 1) * sizeof(ll));
    memset(reachable, 0, (min_a + 1) * sizeof(ll));
    reachable[0] = 1;

    for (ll i = 0; i < n; i++) {
        for (ll j = a[i]; j <= min_a; j++) {
            if (reachable[j - a[i]]) {
                reachable[j] = 1;
            }
        }
    }

    ll count = 0;
    for (ll i = 0; i < min_a; i++) {
        if (reachable[i]) {
            ll start = (l - i + min_a - 1) / min_a * min_a + i;
            ll end = (r - i) / min_a * min_a + i;
            if (start <= end) {
                count += (end - start) / min_a + 1;
            }
        }
    }

    free(reachable);
    return count;
}

int main() {
    ll n, l, r;
    scanf("%lld %lld %lld", &n, &l, &r);
    ll a[MAXN];
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    ll result = solve(n, a, l, r);
    printf("%lld\n", result);

    return 0;
}