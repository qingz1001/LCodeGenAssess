#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int prices[m], weights[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &prices[i], &weights[i]);
    }
    
    int dp[n + 1];
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = n; j >= prices[i]; j--) {
            dp[j] = (dp[j] > dp[j - prices[i]] + prices[i] * weights[i]) ? dp[j] : dp[j - prices[i]] + prices[i] * weights[i];
        }
    }
    
    printf("%d\n", dp[n]);
    return 0;
}