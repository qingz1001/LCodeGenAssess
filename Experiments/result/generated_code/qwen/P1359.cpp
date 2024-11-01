#include <stdio.h>
#include <stdlib.h>

#define MAXN 200

int main() {
    int n;
    scanf("%d", &n);
    
    int r[MAXN][MAXN];
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            scanf("%d", &r[i][j]);
        }
    }
    
    int dp[MAXN][MAXN];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                dp[i][j] = 0;
            } else if (i == j - 1) {
                dp[i][j] = r[i][j];
            } else {
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = fmin(dp[i][j], dp[i][k] + dp[k + 1][j] + r[i][j]);
                }
            }
        }
    }
    
    printf("%d\n", dp[1][n]);
    
    return 0;
}