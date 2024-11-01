#include <stdio.h>
#include <string.h>

#define MAXN 85
#define MAXM 85
#define LL long long

LL dp[MAXM][MAXM][MAXM];
LL a[MAXN][MAXM];
int n, m;

void solve() {
    for (int k = 1; k <= m; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (j < k) {
                    dp[i][j][k] = -1;
                } else if (j == k) {
                    dp[i][j][k] = dp[i][j][k-1] + (1LL << (k-1)) * a[i][j];
                } else {
                    dp[i][j][k] = dp[i][j-1][k-1] + (1LL << (k-1)) * a[i][j];
                    if (j > k) {
                        dp[i][j][k] = dp[i][j][k] > dp[i][j-1][k] + (1LL << (k-1)) * a[i][j] ? dp[i][j][k] : dp[i][j-1][k] + (1LL << (k-1)) * a[i][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    memset(dp, 0, sizeof(dp));
    solve();
    LL maxn = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            maxn = maxn > dp[i][j][m] ? maxn : dp[i][j][m];
        }
    }
    printf("%lld\n", maxn);
    return 0;
}