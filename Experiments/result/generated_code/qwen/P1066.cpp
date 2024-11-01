#include <stdio.h>

int main() {
    int k, w;
    scanf("%d %d", &k, &w);
    long long dp[w + 1][k + 1];
    for (int i = 0; i <= w; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i <= k; i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= w; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    long long result = 0;
    for (int i = 2; i <= k; i++) {
        result += dp[w][i];
    }
    printf("%lld\n", result);
    return 0;
}