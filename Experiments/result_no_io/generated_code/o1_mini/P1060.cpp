#include <stdio.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int dp[30001];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<m;i++){
        int v, p;
        scanf("%d %d", &v, &p);
        int val = v * p;
        for(int j=n; j>=v; j--){
            if(dp[j - v] + val > dp[j]){
                dp[j] = dp[j - v] + val;
            }
        }
    }
    int max = 0;
    for(int i=0;i<=n;i++) if(dp[i] > max) max = dp[i];
    printf("%d", max);
    return 0;
}