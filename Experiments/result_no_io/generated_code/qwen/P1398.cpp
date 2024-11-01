#include <stdio.h>
#include <stdlib.h>

#define MAXN 151
#define MAXM 501

int n, m;
int grid[MAXN][MAXM];
int dp[MAXN][MAXM][4];

void init() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k < 4; ++k) {
                dp[i][j][k] = -1e9;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }

    init();
    dp[1][1][0] = grid[1][1];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j][0] = dp[i-1][j][0] + grid[i][j];
            dp[i][j][1] = dp[i][j-1][1] + grid[i][j];
            dp[i][j][2] = dp[i-1][j-1][2] + grid[i][j];
        }
    }

    int max_lucky = -1e9;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i >= 3 && j >= 3) {
                int lucky_n = dp[i-1][j][0] + dp[i][j-1][1] - dp[i-1][j-1][2] - grid[i][j];
                max_lucky = fmax(max_lucky, lucky_n);
            }
            if (i >= 3 && j >= 3) {
                int lucky_o = dp[i-1][j][0] + dp[i][j-1][1] - dp[i-1][j-1][2] - grid[i][j];
                lucky_o -= dp[i-3][j-3][0] + dp[i-2][j-2][1] - dp[i-3][j-2][2] - grid[i-3][j-3];
                max_lucky = fmax(max_lucky, lucky_o);
            }
            if (i >= 3 && j >= 3) {
                int lucky_i = dp[i-1][j][0] + dp[i][j-1][1] - dp[i-1][j-1][2] - grid[i][j];
                lucky_i += dp[i-1][j-1][0] + dp[i][j-1][1] - dp[i-1][j][2] - grid[i][j-1];
                lucky_i += dp[i-1][j-1][0] + dp[i][j-1][1] - dp[i][j-2][2] - grid[i][j];
                max_lucky = fmax(max_lucky, lucky_i);
            }
        }
    }

    printf("%d\n", max_lucky);

    return 0;
}