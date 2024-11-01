#include <stdio.h>
#include <stdlib.h>

#define MAXN 105
#define INF 1e9

int dp[MAXN][MAXN];
long long pyramid[MAXN][MAXN];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%lld", &pyramid[i][j]);
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = -INF;
        }
    }
    
    dp[1][1] = pyramid[1][1];
    
    for (int i = 2; i <= n; ++i) {
        dp[i][1] = dp[i-1][1] + pyramid[i][1];
        dp[i][i] = dp[i-1][i-1] + pyramid[i][i];
        for (int j = 2; j < i; ++j) {
            dp[i][j] = fmax(dp[i-1][j-1], dp[i-1][j]) + pyramid[i][j];
        }
    }
    
    long long max_score = -INF;
    for (int i = 1; i <= n; ++i) {
        if (k >= i-1) {
            max_score = fmax(max_score, dp[n][i] * 3 + pyramid[n][i]);
        } else {
            max_score = fmax(max_score, dp[n][i]);
        }
    }
    
    printf("%lld\n", max_score);
    
    return 0;
}