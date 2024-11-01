#include <stdio.h>
#include <limits.h>

int main(){
    int n;
    scanf("%d", &n);
    int r[201][201];
    for(int i=1;i<=n;i++) {
        for(int j=i+1;j<=n;j++) {
            scanf("%d", &r[i][j]);
        }
    }
    int dp[201];
    for(int i=1;i<=n;i++) dp[i] = INT32_MAX;
    dp[1] = 0;
    for(int i=1;i<=n;i++) {
        for(int j=i+1;j<=n;j++) {
            if(dp[i] != INT32_MAX && dp[j] > dp[i] + r[i][j]){
                dp[j] = dp[i] + r[i][j];
            }
        }
    }
    printf("%d", dp[n]);
    return 0;
}