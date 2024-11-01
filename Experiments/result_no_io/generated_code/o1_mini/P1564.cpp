#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 2501

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int prefix1[n+1], prefix2[n+1];
    prefix1[0]=prefix2[0]=0;
    for(int i=1;i<=n;i++){
        prefix1[i] = prefix1[i-1] + (a[i]==1 ? 1 : 0);
        prefix2[i] = prefix2[i-1] + (a[i]==2 ? 1 : 0);
    }
    int dp[n+1];
    dp[0]=0;
    for(int i=1;i<=n;i++){
        dp[i] = INF;
        for(int j=i-1; j>=0; j--){
            int c1 = prefix1[i] - prefix1[j];
            int c2 = prefix2[i] - prefix2[j];
            if(c1 ==0 || c2 ==0 || abs(c1 - c2) <= m){
                if(dp[j] +1 < dp[i]) dp[i] = dp[j] +1;
            }
        }
    }
    printf("%d\n", dp[n]);
    return 0;
}