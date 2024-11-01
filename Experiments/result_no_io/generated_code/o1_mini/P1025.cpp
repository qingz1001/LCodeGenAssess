#include <stdio.h>
#include <string.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int dp[7][201];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for(int num = 1; num <= n; num++){
        for(int i = k; i >=1; i--){
            for(int j = num; j <=n; j++){
                dp[i][j] += dp[i-1][j - num];
            }
        }
    }
    printf("%d\n", dp[k][n]);
    return 0;
}