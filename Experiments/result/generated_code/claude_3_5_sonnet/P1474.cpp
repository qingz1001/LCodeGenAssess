#include <stdio.h>
#include <string.h>

#define MAX_N 10001
#define MAX_V 26

long long dp[MAX_N];
int coins[MAX_V];

int main() {
    int V, N;
    scanf("%d %d", &V, &N);
    
    for (int i = 0; i < V; i++) {
        scanf("%d", &coins[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    for (int i = 0; i < V; i++) {
        for (int j = coins[i]; j <= N; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    printf("%lld\n", dp[N]);
    
    return 0;
}