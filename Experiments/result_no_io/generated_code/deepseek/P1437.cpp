#include <stdio.h>
#include <string.h>

#define MAXN 51
#define MAXM 1276  // (50 * 51) / 2

int n, m;
int a[MAXN][MAXN];
int dp[MAXN][MAXN][MAXM];

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i + 1; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n - i + 1; j++) {
            for (int k = j; k <= m; k++) {
                for (int l = max(0, j - 1); l <= n - i; l++) {
                    if (dp[i - 1][l][k - j] != -1) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][l][k - j] + a[i][j]);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i + 1; j++) {
            for (int k = 1; k <= m; k++) {
                ans = max(ans, dp[i][j][k]);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}