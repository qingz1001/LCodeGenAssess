#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

int main() {
    int k, w;
    scanf("%d%d", &k, &w);

    if (w < k) {
        printf("0\n");
        return 0;
    }

    int dp[MAX_DIGITS + 1][10];
    memset(dp, 0, sizeof(dp));

    // Initialize the first column
    for (int i = 1; i <= (1 << k) - 1; i++) {
        dp[1][i] = 1;
    }

    // Fill the dp table
    for (int i = 2; i <= w / k; i++) {
        for (int j = 1; j <= (1 << k) - 1; j++) {
            for (int l = 0; l <= j; l++) {
                dp[i][j] += dp[i - 1][l];
            }
        }
    }

    // Calculate the result
    int result = 0;
    for (int i = 1; i <= (1 << k) - 1; i++) {
        result += dp[w / k][i];
    }

    // Output the result
    printf("%d\n", result);

    return 0;
}