#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int scores[MAX_N][MAX_M];
    char rewards[MAX_N][MAX_M];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d %c", &scores[i][j], &rewards[i][j]);
        }
    }

    int dp[n + 1][k + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= j; l++) {
                dp[i][j] = dp[i][j] > dp[i - 1][j - l] + scores[i - 1][l] ? dp[i][j] : dp[i - 1][j - l] + scores[i - 1][l];
                if (rewards[i - 1][l] == 'Y' && j - l - 1 >= 0) {
                    dp[i][j] = dp[i][j] > dp[i - 1][j - l - 1] + scores[i - 1][l] ? dp[i][j] : dp[i - 1][j - l - 1] + scores[i - 1][l];
                }
            }
        }
    }

    printf("%d\n", dp[n][k]);

    return 0;
}