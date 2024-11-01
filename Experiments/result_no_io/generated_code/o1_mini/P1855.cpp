#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main(){
    int n, M, T;
    scanf("%d %d %d", &n, &M, &T);
    int m[n], t[n];
    for(int i=0;i<n;i++) scanf("%d %d", &m[i], &t[i]);
    int dp[M+1][T+1];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<n;i++){
        for(int mm=M; mm>=m[i]; mm--){
            for(int tt=T; tt>=t[i]; tt--){
                if(dp[mm - m[i]][tt - t[i]] + 1 > dp[mm][tt]){
                    dp[mm][tt] = dp[mm - m[i]][tt - t[i]] +1;
                }
            }
        }
    }
    int res=0;
    for(int mm=0; mm<=M; mm++) {
        for(int tt=0; tt<=T; tt++) {
            if(dp[mm][tt] > res) res = dp[mm][tt];
        }
    }
    printf("%d", res);
    return 0;
}