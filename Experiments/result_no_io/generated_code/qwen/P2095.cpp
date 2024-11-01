#include <stdio.h>
#include <stdlib.h>

#define MAX_N 205
#define MAX_M 105
#define MAX_K 105

int dp[MAX_N][MAX_M][MAX_K];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int limit[MAX_K];
    for (int i = 0; i < k; i++) {
        scanf("%d", &limit[i]);
    }

    int fat[MAX_N], category[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &fat[i], &category[i]);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int l = 0; l <= k; l++) {
                dp[i][j][l] = -1;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int l = 0; l <= k; l++) {
                if (dp[i-1][j][l] == -1) continue;
                if (l >= category[i-1]) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i-1][j][l] + fat[i-1]);
                }
                if (j >= 1 && l >= category[i-1]) {
                    dp[i][j][l] = max(dp[i][j][l], dp[i-1][j-1][l] + fat[i-1]);
                }
            }
        }
    }

    int result = -1;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= k; j++) {
            result = max(result, dp[n][i][j]);
        }
    }

    printf("%d\n", result);

    return 0;
}