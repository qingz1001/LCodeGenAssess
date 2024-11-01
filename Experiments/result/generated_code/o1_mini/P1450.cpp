#include<stdio.h>
#include<string.h>

#define MAX_S 100005

int main(){
    int c[4];
    int n;
    scanf("%d %d %d %d %d", &c[0], &c[1], &c[2], &c[3], &n);
    int d[4], s;
    int dp[MAX_S];
    for(int q=0; q<n; q++){
        scanf("%d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &s);
        memset(dp, 0, sizeof(int)*(s+1));
        dp[0] = 1;
        for(int i=0; i<4; i++){
            for(int j=0; j<=s; j++){
                if(j >= c[i]){
                    dp[j] += dp[j - c[i]];
                    if(j >= c[i]*(d[i]+1)){
                        dp[j] -= dp[j - c[i]*(d[i]+1)];
                    }
                }
            }
        }
        printf("%d\n", dp[s]);
    }
    return 0;
}