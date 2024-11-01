#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXK 5050

int n, k;
long long pyramid[MAXN][MAXN];
long long dp[MAXN][MAXN][MAXK];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%lld", &pyramid[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int l = 0; l <= k; l++) {
                dp[i][j][l] = LLONG_MIN;
            }
        }
    }

    dp[0][0][0] = pyramid[0][0];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j <= i; j++) {
            for (int l = 0; l <= k; l++) {
                if (dp[i][j][l] != LLONG_MIN) {
                    // Move to the left child
                    dp[i + 1][j][l] = max(dp[i + 1][j][l], dp[i][j][l] + pyramid[i + 1][j]);
                    // Move to the right child
                    dp[i + 1][j + 1][l] = max(dp[i + 1][j + 1][l], dp[i][j][l] + pyramid[i + 1][j + 1]);
                    // Use the power-up on the left child
                    if (l < k) {
                        dp[i + 1][j][l + 1] = max(dp[i + 1][j][l + 1], dp[i][j][l] + 3 * pyramid[i + 1][j]);
                    }
                    // Use the power-up on the right child
                    if (l < k) {
                        dp[i + 1][j + 1][l + 1] = max(dp[i + 1][j + 1][l + 1], dp[i][j][l] + 3 * pyramid[i + 1][j + 1]);
                    }
                }
            }
        }
    }

    long long result = LLONG_MIN;
    for (int j = 0; j < n; j++) {
        for (int l = 0; l <= k; l++) {
            result = max(result, dp[n - 1][j][l]);
        }
    }

    printf("%lld\n", result);
    return 0;
}