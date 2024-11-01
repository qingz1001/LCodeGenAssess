#include<stdio.h>
#include<string.h>

#define MOD 9901
#define MAXN 201
#define MAXK 101

long long dp[MAXN][MAXK];

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    memset(dp, 0, sizeof(dp));
    for(int depth=1; depth<=k; depth++){
        for(int nodes=1; nodes<=n; nodes++){
            if(nodes ==1){
                dp[nodes][depth] =1;
            }
            else if(nodes %2 ==1){
                long long total =0;
                for(int left=1; left<nodes; left+=2){
                    int right = nodes -1 - left;
                    total += dp[left][depth-1] * dp[right][depth-1];
                    total %= MOD;
                }
                dp[nodes][depth] = total;
            }
            else{
                dp[nodes][depth] =0;
            }
        }
    }
    long long ans =0;
    if(k==0){
        ans =0;
    }
    else{
        ans = dp[n][k];
        if(k-1 >=1){
            ans -= dp[n][k-1];
            if(ans <0) ans += MOD;
        }
    }
    printf("%lld\n", ans % MOD);
    return 0;
}