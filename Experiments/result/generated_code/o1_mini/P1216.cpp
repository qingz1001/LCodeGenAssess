#include<stdio.h>
#include<stdlib.h>

int main(){
    int r;
    scanf("%d", &r);
    int dp[1001]={0};
    for(int i=1;i<=r;i++){
        for(int j=i; j>=1; j--){
            int a;
            scanf("%d", &a);
            if(j==1){
                dp[j] = dp[j] + a;
            }
            else{
                if(dp[j] > dp[j-1]){
                    dp[j] = dp[j] + a;
                }
                else{
                    dp[j] = dp[j-1] + a;
                }
            }
        }
    }
    int max = 0;
    for(int i=1;i<=r;i++) if(dp[i]>max) max = dp[i];
    printf("%d", max);
    return 0;
}