#include <stdio.h>
#include <string.h>

int main(){
    int n, M, T;
    scanf("%d %d %d", &n, &M, &T);
    int m_i, t_i;
    int dp[201][201];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<n;i++){
        scanf("%d %d", &m_i, &t_i);
        for(int m = M; m >= m_i; m--){
            for(int t = T; t >= t_i; t--){
                if(dp[m - m_i][t - t_i] +1 > dp[m][t]){
                    dp[m][t] = dp[m - m_i][t - t_i] +1;
                }
            }
        }
    }
    int max_count = 0;
    for(int m=0; m<=M; m++){
        for(int t=0; t<=T; t++){
            if(dp[m][t] > max_count){
                max_count = dp[m][t];
            }
        }
    }
    printf("%d\n", max_count);
    return 0;
}