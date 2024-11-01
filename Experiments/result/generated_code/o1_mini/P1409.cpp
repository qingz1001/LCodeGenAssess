#include <stdio.h>
#include <string.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    double dp[1001][1001];
    memset(dp, 0, sizeof(dp));
    dp[1][1] = 1.0;
    for(int k=2; k<=n; k++){
        for(int p=k; p>=1; p--){
            if(p ==1){
                dp[k][p] = (1.0 /6.0) + (3.0 /6.0)*dp[k][k];
            }
            else{
                dp[k][p] = (3.0 /6.0)*dp[k][p-1] + (2.0 /6.0)*dp[k-1][p-1];
            }
        }
    }
    printf("%.9lf\n", dp[n][m]);
    return 0;
}