#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long dp[m+1][n+1];
    for(int i=0;i<=m;i++) {
        for(int j=1;j<=n;j++) dp[i][j]=0;
    }
    dp[0][1]=1;
    for(int k=1;k<=m;k++){
        for(int j=1;j<=n;j++){
            int left = (j ==1)?n:j-1;
            int right = (j ==n)?1:j+1;
            dp[k][j] = dp[k-1][left] + dp[k-1][right];
        }
    }
    printf("%lld", dp[m][1]);
    return 0;
}