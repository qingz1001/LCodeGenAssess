#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int V, N;
    scanf("%d %d", &V, &N);
    int *coins = (int*)malloc(V * sizeof(int));
    for(int i=0;i<V;i++) scanf("%d", &coins[i]);
    ll *dp = (ll*)calloc(N+1, sizeof(ll));
    dp[0] = 1;
    for(int i=0;i<V;i++){
        int coin = coins[i];
        for(int j=coin; j<=N; j++) {
            dp[j] += dp[j - coin];
        }
    }
    printf("%lld\n", dp[N]);
    free(coins);
    free(dp);
    return 0;
}