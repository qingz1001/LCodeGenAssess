#include <stdio.h>
#define MAXN 10

int grid[MAXN][MAXN];
int n;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int dp[MAXN][MAXN][2];

int solve() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = -1;
        }
    }

    dp[0][0][0] = grid[0][0];
    for (int i = 1; i <= n; i++) {
        if (grid[i][0]) {
            dp[i][0][0] = dp[i-1][0][0] + grid[i][0];
        }
    }
    for (int j = 1; j <= n; j++) {
        if (grid[0][j]) {
            dp[0][j][0] = dp[0][j-1][0] + grid[0][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j]) {
                dp[i][j][0] = max(dp[i-1][j][0], dp[i][j-1][0]) + grid[i][j];
            }
        }
    }

    for (int i = n; i >= 0; i--) {
        for (int j = n; j >= 0; j--) {
            dp[i][j][1] = -1;
        }
    }

    dp[n][n][1] = 0;
    for (int i = n-1; i >= 0; i--) {
        if (grid[i][n]) {
            dp[i][n][1] = dp[i+1][n][1] + grid[i][n];
        }
    }
    for (int j = n-1; j >= 0; j--) {
        if (grid[n][j]) {
            dp[n][j][1] = dp[n][j+1][1] + grid[n][j];
        }
    }

    for (int i = n-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            if (grid[i][j]) {
                dp[i][j][1] = max(dp[i+1][j][1], dp[i][j+1][1]);
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j][0] != -1 && dp[i][j][1] != -1) {
                result = max(result, dp[i][j][0] + dp[i][j][1]);
            }
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);
    while (1) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        if (x == 0 && y == 0 && v == 0) break;
        grid[x-1][y-1] = v;
    }

    printf("%d\n", solve());

    return 0;
}