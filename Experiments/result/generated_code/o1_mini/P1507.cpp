#include <stdio.h>
#include <string.h>

int main(){
    int H, T;
    scanf("%d %d", &H, &T);
    int n;
    scanf("%d", &n);
    int h_i, t_i, k_i;
    int dp[401][401];
    memset(dp, 0, sizeof(dp));
    for(int item=0; item<n; item++){
        scanf("%d %d %d", &h_i, &t_i, &k_i);
        for(int h = H; h >= h_i; h--){
            for(int t = T; t >= t_i; t--){
                if(dp[h - h_i][t - t_i] + k_i > dp[h][t]){
                    dp[h][t] = dp[h - h_i][t - t_i] + k_i;
                }
            }
        }
    }
    int max_k = 0;
    for(int h=0; h<=H; h++){
        for(int t=0; t<=T; t++){
            if(dp[h][t] > max_k){
                max_k = dp[h][t];
            }
        }
    }
    printf("%d", max_k);
    return 0;
}