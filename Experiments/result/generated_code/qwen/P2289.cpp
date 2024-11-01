#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // Initialize the dp table
    long long dp[m+1][n+1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    
    // Base case: there is one way to stay at the starting point
    dp[0][0] = 1;
    
    // Fill the dp table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i > 0) {
                dp[i][j] += dp[i-1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j-1];
            }
        }
    }
    
    // Output the result
    printf("%lld\n", dp[m][n]);
    
    return 0;
}