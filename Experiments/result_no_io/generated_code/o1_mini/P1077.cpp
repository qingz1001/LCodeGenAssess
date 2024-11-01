#include <stdio.h>
#define MOD 1000007

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=m;j++) dp[i][j]=0;
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0; k<=a[i] && k<=j; k++){
                dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % MOD;
            }
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}