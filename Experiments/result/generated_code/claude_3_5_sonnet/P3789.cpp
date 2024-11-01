#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXK 100005
#define MAXN 3

typedef long long ll;

ll n, k;
ll dp[2][MAXK][MAXN][MAXN];

void add(ll *a, ll b) {
    *a = (*a + b) % MOD;
}

int main() {
    scanf("%lld %lld", &n, &k);

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = dp[0][0][1][1] = dp[0][0][2][2] = 1;

    int cur = 0, nxt = 1;
    for (int i = 1; i < n; i++) {
        memset(dp[nxt], 0, sizeof(dp[nxt]));
        for (int j = 0; j <= k; j++) {
            for (int l = 0; l < 3; l++) {
                for (int m = 0; m < 3; m++) {
                    if (l == 0 && m == 0) continue;
                    if (l == 1 && m == 1) continue;
                    
                    add(&dp[nxt][j][l][m], dp[cur][j][m][0]);
                    add(&dp[nxt][j][l][m], dp[cur][j][m][2]);
                    
                    if (j > 0 && ((l == 0 && m == 1) || (l == 1 && m == 0))) {
                        add(&dp[nxt][j][l][m], dp[cur][j-1][m][0]);
                        add(&dp[nxt][j][l][m], dp[cur][j-1][m][1]);
                        add(&dp[nxt][j][l][m], dp[cur][j-1][m][2]);
                    }
                }
            }
        }
        cur ^= 1;
        nxt ^= 1;
    }

    for (int i = 0; i <= k; i++) {
        ll ans = 0;
        for (int j = 0; j < 3; j++) {
            for (int l = 0; l < 3; l++) {
                add(&ans, dp[cur][i][j][l]);
            }
        }
        printf("%lld ", ans);
    }

    return 0;
}