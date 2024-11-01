#include <stdio.h>
#include <stdlib.h>

#define MAX 2501
#define INF 2501

int min(int a, int b){
    return a < b ? a : b;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    
    int prefix1[n+1];
    int prefix2[n+1];
    prefix1[0] = prefix2[0] = 0;
    for(int i=1;i<=n;i++){
        prefix1[i] = prefix1[i-1] + (a[i]==1 ? 1 : 0);
        prefix2[i] = prefix2[i-1] + (a[i]==2 ? 1 : 0);
    }
    
    int dp[n+1];
    dp[0] = 0;
    for(int i=1;i<=n;i++) dp[i] = INF;
    
    for(int i=1;i<=n;i++){
        for(int j=i-1;j>=0;j--){
            int cnt1 = prefix1[i] - prefix1[j];
            int cnt2 = prefix2[i] - prefix2[j];
            if(cnt1 == 0 || cnt2 == 0 || abs(cnt1 - cnt2) <= m){
                if(dp[j] + 1 < dp[i]){
                    dp[i] = dp[j] + 1;
                }
            }
        }
    }
    
    printf("%d\n", dp[n]);
    return 0;
}