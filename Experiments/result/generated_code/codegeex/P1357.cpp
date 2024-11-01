#include <stdio.h>
#include <string.h>

#define MOD 1000000007

typedef long long ll;

ll n, m, k;
ll dp[2][32][32][32][32];
ll now, pre;

void init() {
    now = 0;
    pre = 1;
    memset(dp[now], 0, sizeof(dp[now]));
    dp[now][0][0][0][0] = 1;
}

void swap() {
    now = 1 - now;
    pre = 1 - pre;
}

ll solve() {
    for (ll i = 1; i <= n; i++) {
        memset(dp[now], 0, sizeof(dp[now]));
        for (ll j = 0; j < m; j++) {
            for (ll p = 0; p <= k; p++) {
                for (ll q = 0; q <= k; q++) {
                    for (ll r = 0; r <= k; r++) {
                        ll &f = dp[now][j][p][q][r];
                        ll &g = dp[pre][j][p][q][r];
                        if (!g) continue;
                        if (j < m - 1) {
                            f = (f + g) % MOD;
                        }
                        if (j >= 1) {
                            if (p < k) {
                                f = (f + g) % MOD;
                            }
                            if (q < k) {
                                f = (f + g) % MOD;
                            }
                            if (r < k) {
                                f = (f + g) % MOD;
                            }
                        }
                    }
                }
            }
        }
        swap();
    }
    ll ans = 0;
    for (ll j = 0; j < m; j++) {
        for (ll p = 0; p <= k; p++) {
            for (ll q = 0; q <= k; q++) {
                for (ll r = 0; r <= k; r++) {
                    ans = (ans + dp[pre][j][p][q][r]) % MOD;
                }
            }
        }
    }
    return ans;
}

int main() {
    scanf("%lld %lld %lld", &n, &m, &k);
    init();
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}