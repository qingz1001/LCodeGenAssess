#include <stdio.h>
#include <stdlib.h>

#define MAX_N 21
#define MAX_M 1001

int dp[MAX_N][MAX_M];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1) continue;
            if (i + 1 <= n) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j + 1 <= m) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            if (i + 1 <= n && j + 1 <= m) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
        }
    }

    printf("%d\n", dp[n][m]);

    return 0;
}