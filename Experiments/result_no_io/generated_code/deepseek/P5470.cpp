#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXK 200005
#define MAXL 200005
#define INF 1000000000000000000LL

typedef long long ll;

int n, K, L;
ll a[MAXN], b[MAXN];
ll sum_a[MAXN], sum_b[MAXN];
ll dp[MAXK][MAXL];

void solve() {
    scanf("%d %d %d", &n, &K, &L);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);

    for (int i = 1; i <= K; i++) {
        for (int j = 0; j <= L; j++) {
            dp[i][j] = -INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        sum_a[i] = sum_a[i - 1] + a[i];
        sum_b[i] = sum_b[i - 1] + b[i];
    }

    for (int i = 1; i <= K; i++) {
        for (int j = 0; j <= L; j++) {
            if (i == 1 && j == 0) {
                dp[i][j] = sum_a[i] + sum_b[i];
            } else if (i > 1 && j == 0) {
                dp[i][j] = dp[i - 1][j] + a[i] + b[i];
            } else if (i == 1 && j > 0) {
                dp[i][j] = dp[i][j - 1] + a[i] + b[i];
            } else {
                dp[i][j] = dp[i - 1][j] + a[i] + b[i];
                if (j > 0) dp[i][j] = dp[i][j - 1] + a[i] + b[i];
            }
        }
    }

    ll ans = -INF;
    for (int i = K; i <= n; i++) {
        for (int j = L; j <= K; j++) {
            ans = (ans > dp[i][j]) ? ans : dp[i][j];
        }
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