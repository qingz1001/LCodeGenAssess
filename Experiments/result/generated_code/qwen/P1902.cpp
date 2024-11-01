#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define INF 0x3f3f3f3f

int n, m;
int p[MAXN][MAXN];
int dp[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &p[i][j]);
        }
    }

    for (int i = 1; i <= m; ++i) {
        dp[1][i] = p[1][i];
    }

    for (int i = 2; i <= n - 1; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = INF;
            for (int k = 1; k <= m; ++k) {
                dp[i][j] = min(dp[i][j], max(p[i][j], dp[i - 1][k]));
            }
        }
    }

    int ans = INF;
    for (int i = 1; i <= m; ++i) {
        ans = min(ans, dp[n - 1][i]);
    }

    printf("%d\n", ans);

    return 0;
}