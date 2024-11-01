#include <stdio.h>
#include <limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int r[n+1][n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            r[i][j] = INT_MAX;
        }
    }
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            scanf("%d", &r[i][j]);
        }
    }
    long long dp[n+1];
    for(int i=1;i<=n;i++) dp[i] = INT32_MAX;
    dp[1] = 0;
    for(int i=1;i<=n;i++){
        if(dp[i]==INT32_MAX) continue;
        for(int j=i+1;j<=n;j++){
            if(r[i][j] != INT32_MAX && dp[j] > dp[i] + r[i][j]){
                dp[j] = dp[i] + r[i][j];
            }
        }
    }
    printf("%lld\n", dp[n]);
    return 0;
}