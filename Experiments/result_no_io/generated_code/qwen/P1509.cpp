#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define INF 0x3f3f3f3f

typedef struct {
    int rmb;
    int rp;
    int time;
} MM;

int dp[MAXN][MAXN];

int main() {
    int n, m, r;
    scanf("%d", &n);
    MM mm[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }
    scanf("%d %d", &m, &r);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i-1][j] != INF) {
                dp[i][j] = dp[i-1][j];
            }
            if (j >= mm[i].rmb && r >= mm[i].rp) {
                dp[i][j] = fmin(dp[i][j], dp[i-1][j-mm[i].rmb] + mm[i].time);
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= m; i++) {
        ans = fmin(ans, dp[n][i]);
    }

    printf("%d\n", ans == INF ? 0 : ans);

    return 0;
}