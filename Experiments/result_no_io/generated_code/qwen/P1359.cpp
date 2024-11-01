#include <stdio.h>
#include <limits.h>

#define MAXN 205

int main() {
    int n;
    scanf("%d", &n);
    
    int r[MAXN][MAXN];
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            scanf("%d", &r[i][j]);
        }
    }
    
    int dp[MAXN];
    for (int i = 1; i <= n; ++i) {
        dp[i] = INT_MAX;
    }
    dp[1] = 0;
    
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (dp[j] != INT_MAX && r[j][i] != 0) {
                dp[i] = (dp[i] > dp[j] + r[j][i]) ? dp[j] + r[j][i] : dp[i];
            }
        }
    }
    
    printf("%d\n", dp[n]);
    
    return 0;
}