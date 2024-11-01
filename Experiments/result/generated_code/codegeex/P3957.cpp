#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000
#define MAX_VAL 1000000000

typedef long long ll;

ll n, d, k;
ll x[MAX_N], s[MAX_N];
ll dp[MAX_N];

ll get_min_coins(ll max_val) {
    ll left = 0, right = max_val, mid;
    while (left < right) {
        mid = (left + right) / 2;
        ll sum = 0;
        for (ll i = 0; i < n; i++) {
            if (dp[i] < 0) continue;
            ll max_j = (x[i] + d + mid - 1) / (d + mid);
            ll min_j = (x[i] + 1 - mid) / (d + mid);
            if (min_j < 0) min_j = 0;
            if (min_j <= i && i < max_j) {
                dp[i] += s[i];
            } else {
                dp[i] = -1;
            }
            sum += dp[i];
        }
        if (sum >= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%lld %lld %lld", &n, &d, &k);
    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld", &x[i], &s[i]);
    }

    ll max_val = 0;
    for (ll i = 0; i < n; i++) {
        max_val = (x[i] + d - 1) / d;
    }

    ll min_coins = get_min_coins(max_val);
    if (min_coins > max_val) {
        printf("-1\n");
    } else {
        printf("%lld\n", min_coins);
    }

    return 0;
}