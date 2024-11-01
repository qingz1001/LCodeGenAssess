#include <stdio.h>

int countWays(int n, int k) {
    int dp[201][7] = {0};
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int x = i; x >= 1; x--) {
                dp[i][j] += dp[x-1][j-1];
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", countWays(n, k));
    return 0;
}