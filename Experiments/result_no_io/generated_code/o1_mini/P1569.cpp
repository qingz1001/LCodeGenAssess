#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    long long sum[n+1];
    sum[0] = 0;
    for(int i=1;i<=n;i++) sum[i] = sum[i-1] + a[i];
    
    int dp[n+1];
    for(int i=0;i<=n;i++) dp[i] = -1;
    dp[0] = 0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(sum[i] - sum[j-1] >=0 && dp[j-1] != -1){
                if(dp[i] < dp[j-1] +1){
                    dp[i] = dp[j-1] +1;
                }
            }
        }
    }
    
    if(dp[n] != -1){
        printf("%d\n", dp[n]);
    }
    else{
        printf("Impossible\n");
    }
    
    return 0;
}