#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define INF -1000000000

long long pre[MAX_N];
int dp[MAX_N];

int main(){
    int n;
    scanf("%d", &n);
    long long a[n+1];
    pre[0] = 0;
    for(int i=1;i<=n;i++){
        scanf("%lld", &a[i]);
        pre[i] = pre[i-1] + a[i];
    }
    for(int i=0;i<=n;i++) dp[i] = INF;
    dp[0] = 0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            if(pre[i] - pre[j] >=0 && dp[j] != INF){
                if(dp[j] +1 > dp[i]){
                    dp[i] = dp[j] +1;
                }
            }
        }
    }
    if(dp[n] != INF){
        printf("%d\n", dp[n]);
    }
    else{
        printf("Impossible\n");
    }
    return 0;
}