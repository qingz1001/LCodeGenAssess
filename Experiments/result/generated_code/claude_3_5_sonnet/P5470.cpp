#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_SUM 1000005
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long ll;

int n, K, L;
ll a[MAX_N], b[MAX_N];
ll dp[MAX_N][205][205];
ll sum[MAX_N];

void solve() {
    scanf("%d%d%d", &n, &K, &L);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);

    for (int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i] + b[i];

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = dp[i-1][j][k];
                if (j > 0) dp[i][j][k] = (dp[i][j][k] > dp[i-1][j-1][k] + a[i]) ? dp[i][j][k] : dp[i-1][j-1][k] + a[i];
                if (k > 0) dp[i][j][k] = (dp[i][j][k] > dp[i-1][j][k-1] + b[i]) ? dp[i][j][k] : dp[i-1][j][k-1] + b[i];
                if (j > 0 && k > 0) dp[i][j][k] = (dp[i][j][k] > dp[i-1][j-1][k-1] + a[i] + b[i]) ? dp[i][j][k] : dp[i-1][j-1][k-1] + a[i] + b[i];
            }
        }
    }

    ll ans = -INF;
    for (int i = L; i <= K; i++) {
        ans = (ans > dp[n][K][K] - sum[n] + sum[i]) ? ans : dp[n][K][K] - sum[n] + sum[i];
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}