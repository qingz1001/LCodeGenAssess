#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_SUM_N 1000005

typedef long long ll;

int n, K, L;
int a[MAX_N], b[MAX_N];
ll dp[MAX_N][205][205];
ll sum_a[MAX_N], sum_b[MAX_N];

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void solve() {
    scanf("%d %d %d", &n, &K, &L);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum_a[i] = sum_a[i-1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        sum_b[i] = sum_b[i-1] + b[i];
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = dp[i-1][j][k];
                if (j > 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + a[i]);
                if (k > 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + b[i]);
                if (j > 0 && k > 0) dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1] + a[i] + b[i]);
            }
        }
    }

    ll ans = -1;
    for (int i = L; i <= K; i++) {
        ans = max(ans, dp[n][K][K] - sum_a[n] - sum_b[n] + sum_a[K] + sum_b[K] + dp[n][i][i]);
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}