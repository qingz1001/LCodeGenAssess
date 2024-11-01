#include <stdio.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int v[m], p[m], vp[m];
    for(int i=0;i<m;i++){
        scanf("%d %d", &v[i], &p[i]);
        vp[i] = v[i] * p[i];
    }
    int dp[n+1];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<m;i++){
        for(int j=n; j>=v[i]; j--){
            if(dp[j - v[i]] + vp[i] > dp[j]){
                dp[j] = dp[j - v[i]] + vp[i];
            }
        }
    }
    int max = 0;
    for(int j=0; j<=n; j++) {
        if(dp[j] > max){
            max = dp[j];
        }
    }
    printf("%d", max);
    return 0;
}