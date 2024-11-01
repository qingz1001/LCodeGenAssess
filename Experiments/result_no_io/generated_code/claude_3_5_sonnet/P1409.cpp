#include <stdio.h>
#include <math.h>

#define MAX_N 1001

double dp[MAX_N][MAX_N];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        dp[1][i] = 1.0;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (1.0 / 6.0) * dp[i-1][j];
            if (j == 1) {
                dp[i][j] += (1.0 / 2.0) * dp[i-1][n];
                dp[i][j] += (1.0 / 3.0) * dp[i-1][n-1];
            } else {
                dp[i][j] += (1.0 / 2.0) * dp[i-1][j-1];
                dp[i][j] += (1.0 / 3.0) * dp[i-1][j-1];
            }
        }
    }

    printf("%.9f\n", dp[n][m]);

    return 0;
}