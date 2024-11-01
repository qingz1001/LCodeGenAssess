#include <stdio.h>
#include <string.h>

#define MAXN 1001

int n, m;
int matrix[MAXN][MAXN];
int dp[MAXN][MAXN][4];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1) dp[i][j][0] = dp[i-1][j][0] + matrix[i][j] == matrix[i-1][j];
            if (j > 1) dp[i][j][1] = dp[i][j-1][1] + matrix[i][j] == matrix[i][j-1];
            if (i > 1 && j > 1) dp[i][j][2] = dp[i-1][j-1][2] + matrix[i][j] == matrix[i-1][j-1];
            if (i > 1 && j > 1) dp[i][j][3] = dp[i-1][j+1][3] + matrix[i][j] == matrix[i-1][j+1];

            for (int k = 0; k <= 3; k++) {
                int min_side = 0;
                if (dp[i][j][k] > 0) {
                    min_side = 1;
                }
                for (int side = 2; side <= dp[i][j][k]; side++) {
                    if (dp[i-side+1][j][k&1] >= side && dp[i][j-side+1][k&2] >= side && dp[i-side+1][j-side+1][k] >= side) {
                        min_side = side;
                    }
                }
                ans += min_side;
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}