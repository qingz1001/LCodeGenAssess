#include <stdio.h>
#include <string.h>

int main(){
    int T, M;
    scanf("%d %d", &T, &M);
    int time[M];
    int value[M];
    for(int i=0;i<M;i++){
        scanf("%d %d", &time[i], &value[i]);
    }
    int dp[T+1];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<M;i++){
        for(int j=T; j>=time[i]; j--){
            if(dp[j - time[i]] + value[i] > dp[j]){
                dp[j] = dp[j - time[i]] + value[i];
            }
        }
    }
    int max = 0;
    for(int i=0;i<=T;i++){
        if(dp[i] > max){
            max = dp[i];
        }
    }
    printf("%d", max);
    return 0;
}