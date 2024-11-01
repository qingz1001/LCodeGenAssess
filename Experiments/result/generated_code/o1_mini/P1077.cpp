#include <stdio.h>
#define MOD 1000007

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=m;j++) dp[i][j] = 0;
    }
    dp[0][0] = 1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            // Not using type i
            dp[i][j] = dp[i-1][j];
            // Using type i
            if(j >=1){
                int t_max = a[i] < j ? a[i] : j;
                for(int t=1;t<=t_max;t++){
                    dp[i][j] += dp[i-1][j-t];
                    if(dp[i][j] >= MOD) dp[i][j] -= MOD;
                }
            }
        }
    }
    printf("%d", dp[n][m]);
    return 0;
}