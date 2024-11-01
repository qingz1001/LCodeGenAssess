#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXM 1005
#define MAXP 1005

int n, m, p;
int coins[MAXN][MAXM];
int cost[MAXN];
int dp[MAXM][MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &coins[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cost[i]);
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[0][1] = 0;

    for (int t = 1; t <= m; t++) {
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int k = 1; k <= p && k <= t; k++) {
                int prev = i - k;
                if (prev <= 0) prev += n;
                sum += coins[prev][t - k + 1];
                dp[t][i] = max(dp[t][i], dp[t - k][prev] + sum - cost[prev]);
            }
        }
    }

    int ans = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[m][i]);
    }

    printf("%d\n", ans);
    return 0;
}