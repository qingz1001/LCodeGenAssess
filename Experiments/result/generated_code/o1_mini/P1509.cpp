#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int count;
    int time;
} DPState;

int main(){
    int n;
    scanf("%d", &n);
    int rmb[n], rp[n], time_arr[n];
    for(int i=0;i<n;i++) scanf("%d %d %d", &rmb[i], &rp[i], &time_arr[i]);
    int m, r;
    scanf("%d %d", &m, &r);
    
    DPState dp[m+1][r+1];
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=r;j++) {
            dp[i][j].count = -1;
            dp[i][j].time = INT32_MAX;
        }
    }
    dp[0][0].count = 0;
    dp[0][0].time = 0;
    
    for(int i=0;i<n;i++) {
        for(int j=m; j>=rmb[i]; j--){
            for(int k=r; k>=rp[i]; k--){
                if(dp[j - rmb[i]][k - rp[i]].count != -1){
                    int new_count = dp[j - rmb[i]][k - rp[i]].count + 1;
                    int new_time = dp[j - rmb[i]][k - rp[i]].time + time_arr[i];
                    if(new_count > dp[j][k].count){
                        dp[j][k].count = new_count;
                        dp[j][k].time = new_time;
                    }
                    else if(new_count == dp[j][k].count && new_time < dp[j][k].time){
                        dp[j][k].time = new_time;
                    }
                }
            }
        }
    }
    
    int max_count = 0;
    int min_total_time = 0;
    for(int j=0;j<=m;j++) {
        for(int k=0;k<=r;k++) {
            if(dp[j][k].count > max_count){
                max_count = dp[j][k].count;
                min_total_time = dp[j][k].time;
            }
            else if(dp[j][k].count == max_count && dp[j][k].count != -1){
                if(dp[j][k].time < min_total_time){
                    min_total_time = dp[j][k].time;
                }
            }
        }
    }
    printf("%d\n", max_count >0 ? min_total_time : 0);
    return 0;
}