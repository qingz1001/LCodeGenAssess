#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_M 25
#define MAX_V 10000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int value[MAX_M], weight[MAX_M];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &value[i], &weight[i]);
    }

    // Initialize the DP array
    int dp[n + 1][6];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= 5; ++j) {
            dp[i][j] = 0;
        }
    }

    // Fill the DP table
    for (int i = 0; i < m; ++i) {
        for (int j = n; j >= value[i]; --j) {
            for (int k = 5; k >= weight[i]; --k) {
                dp[j][k] = fmax(dp[j][k], dp[j - value[i]][k - weight[i]] + value[i] * weight[i]);
            }
        }
    }

    // Find the maximum product sum
    int max_product_sum = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= 5; ++j) {
            max_product_sum = fmax(max_product_sum, dp[i][j]);
        }
    }

    printf("%d\n", max_product_sum);
    return 0;
}