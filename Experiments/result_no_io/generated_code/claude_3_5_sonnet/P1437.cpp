#include <stdio.h>
#include <string.h>

#define MAX_N 51
#define MAX_M 1275  // 50 * 51 / 2

int n, m;
int a[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= m; k++) {
                if (dp[i-1][j-1][k] >= 0) {
                    dp[i][j][k] = dp[i-1][j-1][k];
                }
                if (k >= 1 && dp[i-1][j][k-1] >= 0) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + a[i][j]);
                }
                if (j < i && k >= 2 && dp[i-1][j+1][k-2] >= 0) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j+1][k-2] + a[i][j]);
                }
            }
        }
    }

    int ans = 0;
    for (int j = 1; j <= n; j++) {
        for (int k = 0; k <= m; k++) {
            ans = max(ans, dp[n][j][k]);
        }
    }

    printf("%d\n", ans);

    return 0;
}