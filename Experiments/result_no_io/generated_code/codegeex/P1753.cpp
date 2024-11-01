#include <stdio.h>
#include <limits.h>

#define MAX_N 2000000
#define MAX_VAL 10000

int main() {
    int n;
    scanf("%d", &n);
    
    int w[n+1];
    for (int i = 0; i <= n; i++) {
        scanf("%d", &w[i]);
    }

    long long dp[n+1][n+1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i + 1; j++) {
            int k = j + i - 1;
            dp[j][k] = LLONG_MAX;
            for (int l = j; l < k; l++) {
                dp[j][k] = (dp[j][k] < dp[j][l] + dp[l+1][k] + w[j-1] * w[l] * w[k]) ? dp[j][k] : dp[j][l] + dp[l+1][k] + w[j-1] * w[l] * w[k];
            }
        }
    }
    
    printf("%lld\n", dp[1][n]);
    return 0;
}