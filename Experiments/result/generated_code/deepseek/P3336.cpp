#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 19940417

typedef long long ll;

ll N, K;
ll x[1000005], f[1000005];

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

ll pow_mod(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mod(res * a, m);
        a = mod(a * a, m);
        b >>= 1;
    }
    return res;
}

ll inv(ll a, ll m) {
    return pow_mod(a, m - 2, m);
}

ll solve() {
    if (K == 0) return 1;
    ll max_val = 0;
    for (ll i = 0; i < K; i++) {
        max_val = (max_val > f[i]) ? max_val : f[i];
    }

    ll dp[K + 1][2];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (ll i = 1; i < K; i++) {
        ll dx = x[i] - x[i - 1];
        ll df = f[i] - f[i - 1];
        if (dx < 0 || df < 0 || dx < df) return 0;
        ll ways = pow_mod(2, dx - df, MOD);
        dp[i][0] = mod(dp[i - 1][0] * ways, MOD);
        dp[i][1] = mod(dp[i - 1][1] * ways, MOD);
        if (df > 0) {
            dp[i][1] = mod(dp[i][1] + dp[i - 1][0] * ways % MOD * inv(2, MOD), MOD);
        }
    }

    return dp[K - 1][1];
}

int main() {
    scanf("%lld %lld", &N, &K);
    for (ll i = 0; i < K; i++) {
        scanf("%lld %lld", &x[i], &f[i]);
    }

    ll ways = solve();
    ll max_val = 0;
    for (ll i = 0; i < K; i++) {
        max_val = (max_val > f[i]) ? max_val : f[i];
    }

    printf("%lld %lld\n", ways, max_val);
    return 0;
}