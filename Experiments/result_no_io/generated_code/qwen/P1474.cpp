#include <stdio.h>

int main() {
    int V, N;
    scanf("%d %d", &V, &N);
    
    int coins[V];
    for (int i = 0; i < V; i++) {
        scanf("%d", &coins[i]);
    }
    
    long long dp[N + 1];
    for (int i = 0; i <= N; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;
    
    for (int i = 0; i < V; i++) {
        for (int j = coins[i]; j <= N; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    printf("%lld\n", dp[N]);
    
    return 0;
}