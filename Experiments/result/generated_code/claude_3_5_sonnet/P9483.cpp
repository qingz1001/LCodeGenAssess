#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 101
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long ll;

int n;
ll w[MAX_N];
ll dp[MAX_N][MAX_N];
ll sum[MAX_N];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
        sum[i] = sum[i-1] + w[i];
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                ll cost = dp[i][k] + dp[k+1][j] + sum[j] - sum[i-1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    printf("%lld\n", dp[1][n]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}