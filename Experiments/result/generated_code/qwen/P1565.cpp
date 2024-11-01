#include <stdio.h>
#include <stdlib.h>

#define MAXN 205

int n, m;
int grid[MAXN][MAXN];
int dp[MAXN][MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] > 0) {
                dp[i][j] = 1;
                if (dp[i-1][j] > 0 && grid[i][j] >= grid[i-1][j]) {
                    dp[i][j] += dp[i-1][j];
                }
                if (dp[i][j-1] > 0 && grid[i][j] >= grid[i][j-1]) {
                    dp[i][j] += dp[i][j-1];
                }
                if (dp[i-1][j-1] > 0 && grid[i][j] >= grid[i-1][j-1]) {
                    dp[i][j] += dp[i-1][j-1];
                }
                ans = max(ans, dp[i][j]);
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}