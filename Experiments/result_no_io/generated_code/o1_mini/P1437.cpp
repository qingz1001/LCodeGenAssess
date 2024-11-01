#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRICKS 1275
#define MAX_M 1275
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    // Calculate total bricks
    int total = n*(n+1)/2;
    int a[MAX_BRICKS +1];
    int index =1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i+1;j++){
            scanf("%d", &a[index++]);
        }
    }
    // DP array
    long long dp[MAX_M +1];
    memset(dp, -1, sizeof(dp));
    dp[0] =0;
    for(int k=1; k<index; k++){
        for(int j=m; j>=1; j--){
            if(dp[j-1] != -1){
                if(dp[j] < dp[j-1] + a[k]){
                    dp[j] = dp[j-1] + a[k];
                }
            }
        }
    }
    long long res =0;
    for(int i=0;i<=m;i++) {
        if(dp[i] > res) res = dp[i];
    }
    printf("%lld\n", res);
    return 0;
}