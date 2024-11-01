#include <stdio.h>

typedef long long ll;

int main(){
    int V, N;
    scanf("%d %d", &V, &N);
    int coins[V];
    for(int i=0;i<V;i++) scanf("%d", &coins[i]);
    ll dp[N+1];
    for(int i=0;i<=N;i++) dp[i] = 0;
    dp[0] = 1;
    for(int i=0;i<V;i++){
        int coin = coins[i];
        for(int j=coin; j<=N; j++){
            dp[j] += dp[j - coin];
        }
    }
    printf("%lld\n", dp[N]);
    return 0;
}