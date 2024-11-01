#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXK 100000

typedef long long ll;

ll dp[2][MAXK + 1];

void solve(ll n, int k) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int cur = i & 1;
        int prev = cur ^ 1;
        for (int j = 0; j <= k; ++j) {
            dp[cur][j] = dp[prev][j];
            if (j > 0) {
                dp[cur][j] = (dp[cur][j] + dp[prev][j - 1]) % MOD;
            }
            if (j > 1) {
                dp[cur][j] = (dp[cur][j] - dp[prev][j - 2] + MOD) % MOD;
            }
        }
    }
    for (int i = 0; i <= k; ++i) {
        printf("%lld ", dp[n & 1][i]);
    }
    printf("\n");
}

int main() {
    ll n;
    int k;
    scanf("%lld %d", &n, &k);
    solve(n, k);
    return 0;
}