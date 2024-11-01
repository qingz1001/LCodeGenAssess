#include <stdio.h>
#include <string.h>

#define MAXN 1001

double dp[MAXN][MAXN];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Initialize all to 0
    memset(dp, 0, sizeof(dp));
    
    for(int s =1; s <=n; s++){
        for(int p=1; p<=s; p++){
            if(s ==1){
                dp[s][p] = (p ==1) ? 1.0 : 0.0;
            }
            else{
                if(p ==1){
                    // You are at front
                    // 1/6 win
                    // 3/6 move to end: position becomes s
                    // 2/6 removed: lose
                    dp[s][p] = (1.0/6.0) + (3.0/6.0)*dp[s][s];
                }
                else{
                    // Someone else is at front
                    // 1/6 they win: you lose
                    // 3/6 they move to end: your position becomes p-1
                    // 2/6 they are removed: queue size s-1, your position p-1
                    dp[s][p] = (1.0/6.0)*0.0 + (3.0/6.0)*dp[s][p-1] + (2.0/6.0)*(p-1 <= s-1 ? dp[s-1][p-1] : 0.0);
                }
            }
        }
    }
    
    printf("%.9lf\n", dp[n][m]);
    return 0;
}