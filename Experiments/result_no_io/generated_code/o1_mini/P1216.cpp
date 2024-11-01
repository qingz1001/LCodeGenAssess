#include <stdio.h>

int main(){
    int r;
    scanf("%d", &r);
    int dp[1001][1001];
    for(int i=1;i<=r;i++){
        for(int j=1;j<=i;j++){
            int num;
            scanf("%d", &num);
            if(j ==1){
                dp[i][j] = dp[i-1][j] + num;
            }
            else if(j ==i){
                dp[i][j] = dp[i-1][j-1] + num;
            }
            else{
                if(dp[i-1][j-1] > dp[i-1][j]){
                    dp[i][j] = dp[i-1][j-1] + num;
                }
                else{
                    dp[i][j] = dp[i-1][j] + num;
                }
            }
        }
    }
    int max = dp[r][1];
    for(int j=2;j<=r;j++) if(dp[r][j] > max) max = dp[r][j];
    printf("%d\n", max);
    return 0;
}