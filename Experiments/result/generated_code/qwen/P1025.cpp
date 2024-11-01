#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int dp[n+1][k+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (i < j) {
                dp[i][j] = 0;
            } else if (i == j) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
            }
        }
    }
    printf("%d\n", dp[n][k]);
    return 0;
}