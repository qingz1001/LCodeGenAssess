#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define INF 1e9

typedef long long ll;

int n;
ll D[MAXN], U[MAXN], P[MAXN];
ll M[MAXN], C[MAXN];
ll dp[MAXN][MAXN];

void solve() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (dp[i-1][j] != INF) {
                int produce = j >= D[i] ? D[i] : j;
                int store = j - produce;
                dp[i][produce] = dp[i-1][j] + produce * P[i];
                dp[i][store] = dp[i-1][j] + store * M[i-1];
            }
            if (dp[i-1][j] != INF && j > 0) {
                dp[i][j-1] = dp[i-1][j] + C[i-1];
            }
        }
    }

    ll ans = INF;
    for (int j = 0; j <= n; ++j) {
        if (dp[n][j] != INF) {
            ans = llmin(ans, dp[n][j]);
        }
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &D[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &U[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &P[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%lld", &M[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%lld", &C[i]);
    }
    solve();
    return 0;
}