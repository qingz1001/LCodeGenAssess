#include <stdio.h>
#include <string.h>

#define MAX_N 21
#define MAX_M 1001

int dp[MAX_N + 2][MAX_M + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i][j-1]);
            }
            if (i > 1 && dp[i-1][j] > 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
            }
        }
    }

    int result = dp[n+1][m] - 1;
    printf("%d\n", result);

    return 0;
}