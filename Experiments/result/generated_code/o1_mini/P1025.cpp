#include <stdio.h>
#include <string.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    long long dp[7][201];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int i=1;i<=k;i++){
        for(int j=0;j<=n;j++){
            if(j >=1){
                dp[i][j] += dp[i-1][j-1];
            }
            if(j >= i){
                dp[i][j] += dp[i][j-i];
            }
        }
    }
    printf("%lld\n", dp[k][n]);
    return 0;
}