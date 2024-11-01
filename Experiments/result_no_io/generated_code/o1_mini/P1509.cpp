#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_M 100
#define MAX_R 100
#define INF 1000000000

int main(){
    int n;
    scanf("%d", &n);
    int rmb[MAX_N], rp[MAX_N], time_[MAX_N];
    for(int i=0;i<n;i++) {
        scanf("%d %d %d", &rmb[i], &rp[i], &time_[i]);
    }
    int m, r;
    scanf("%d %d", &m, &r);
    
    // Initialize DP
    // dp[k][x][y] = min time to select k MM with total rmb <=x and rp <=y
    // k ranges from 0 to n
    // x from 0 to m
    // y from 0 to r
    // Initialize all to INF
    int dp[MAX_N+1][MAX_M+1][MAX_R+1];
    for(int k=0;k<=n;k++) {
        for(int x=0;x<=m;x++) {
            for(int y_=0;y_<=r;y_++) {
                dp[k][x][y_] = INF;
            }
        }
    }
    dp[0][0][0] = 0;
    
    for(int i=0;i<n;i++) {
        // Iterate k from current max down to 0
        for(int k = n-1; k >=0; k--){
            for(int x=0; x <=m - rmb[i]; x++) {
                for(int y_=0; y_ <= r - rp[i]; y_++) {
                    if(dp[k][x][y_] != INF){
                        if(dp[k][x][y_] + time_[i] < dp[k+1][x + rmb[i]][y_ + rp[i]]){
                            dp[k+1][x + rmb[i]][y_ + rp[i]] = dp[k][x][y_] + time_[i];
                        }
                    }
                }
            }
        }
    }
    
    // Find the maximum k with any dp[k][x][y] <= INF
    int max_k = 0;
    int min_time = 0;
    for(int k=n; k>=0; k--){
        int found = 0;
        int current_min = INF;
        for(int x=0; x<=m; x++) {
            for(int y_=0; y_<=r; y_++) {
                if(dp[k][x][y_] < current_min){
                    current_min = dp[k][x][y_];
                }
            }
        }
        if(current_min < INF){
            max_k = k;
            min_time = current_min;
            break;
        }
    }
    printf("%d\n", max_k >0 ? min_time : 0);
    return 0;
}