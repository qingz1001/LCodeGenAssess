#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 1000

int n, m, p;
int coins[MAXN][MAXM];
int costs[MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &coins[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &costs[i]);
    }

    int dp[MAXM + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1e9;
        }
    }
    dp[0][0] = 0;

    for (int t = 1; t <= m; t++) {
        for (int k = 0; k < n; k++) {
            for (int r = 1; r <= p; r++) {
                if (dp[t - r][k] != -1e9) {
                    dp[t][k] = max(dp[t][k], dp[t - r][k] + coins[k][t - 1]);
                }
            }
            if (dp[t - 1][k] != -1e9) {
                dp[t][k] = max(dp[t][k], dp[t - 1][k]);
            }
        }
    }

    int ans = -1e9;
    for (int k = 0; k < n; k++) {
        for (int r = 1; r <= p; r++) {
            if (dp[m][k] != -1e9) {
                ans = max(ans, dp[m][k] - costs[k]);
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}