#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXK 100001
#define MAXN 3

typedef long long ll;

ll n, k;
ll dp[2][MAXN][MAXN][MAXK];

void add(ll *a, ll b) {
    *a = (*a + b) % MOD;
}

int main() {
    scanf("%lld %lld", &n, &k);

    memset(dp, 0, sizeof(dp));
    dp[1][0][0][0] = dp[1][1][1][0] = dp[1][2][2][0] = 1;

    int cur = 1, prev = 0;
    for (ll i = 2; i <= n; i++) {
        memset(dp[cur], 0, sizeof(dp[cur]));
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                for (ll m = 0; m <= k; m++) {
                    if (j == 0) {
                        add(&dp[cur][j][0][m], dp[prev][l][1][m]);
                        add(&dp[cur][j][1][m], dp[prev][l][2][m]);
                        add(&dp[cur][j][2][m], dp[prev][l][0][m]);
                    } else if (j == 1) {
                        if (l != 1) {
                            add(&dp[cur][j][0][m], dp[prev][l][1][m]);
                            if (m > 0) add(&dp[cur][j][1][m], dp[prev][l][2][m-1]);
                            add(&dp[cur][j][2][m], dp[prev][l][0][m]);
                        }
                    } else {
                        if (l != 2) {
                            add(&dp[cur][j][0][m], dp[prev][l][1][m]);
                            if (m > 0) add(&dp[cur][j][1][m], dp[prev][l][2][m-1]);
                            add(&dp[cur][j][2][m], dp[prev][l][0][m]);
                        }
                    }
                }
            }
        }
        cur ^= 1;
        prev ^= 1;
    }

    for (ll i = 0; i <= k; i++) {
        ll ans = 0;
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                add(&ans, dp[prev][j][l][i]);
            }
        }
        printf("%lld ", ans);
    }

    return 0;
}