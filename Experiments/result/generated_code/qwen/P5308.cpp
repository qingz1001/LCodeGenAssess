#include <stdio.h>
#include <math.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    double dp[n + 1][k + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = 0.0;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        dp[i][1] = (double)i / n;
    }
    
    for (int j = 2; j <= k; ++j) {
        for (int i = j; i <= n; ++i) {
            dp[i][j] = 0.0;
            for (int x = 1; x < i; ++x) {
                dp[i][j] = fmax(dp[i][j], dp[x][j - 1] * ((double)x / i));
            }
        }
    }
    
    printf("%.9f\n", dp[n][k]);
    
    return 0;
}