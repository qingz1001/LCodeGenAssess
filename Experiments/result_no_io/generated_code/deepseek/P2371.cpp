#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 12
#define MAXA 500000
#define MAXR 1000000000000LL

typedef long long ll;

int n;
ll l, r;
ll a[MAXN];
ll dp[MAXA + 1];

ll min(ll x, ll y) {
    return x < y ? x : y;
}

ll max(ll x, ll y) {
    return x > y ? x : y;
}

ll solve(ll limit) {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    ll min_a = a[0];
    for (int i = 1; i < n; i++) {
        min_a = min(min_a, a[i]);
    }

    for (int i = 0; i < n; i++) {
        for (ll j = a[i]; j <= min_a * limit; j++) {
            dp[j % min_a] = min(dp[j % min_a], dp[j - a[i]] + 1);
        }
    }

    ll count = 0;
    for (ll b = 0; b < min_a; b++) {
        if (dp[b] <= limit) {
            count += (limit - dp[b]) / min_a + 1;
        }
    }

    return count;
}

int main() {
    scanf("%d %lld %lld", &n, &l, &r);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    ll count_l = solve(l - 1);
    ll count_r = solve(r);

    printf("%lld\n", count_r - count_l);

    return 0;
}