#include <stdio.h>
#include <string.h>
#define MAX_M 200
#define MAX_N 200
#define MAX_BULLETS 500
#define INF -1

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Initialize arrays
    int f[MAX_M][MAX_N+1];
    char c_temp[MAX_M][MAX_N+1];
    
    // Read bricks from bottom to top
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            int fi;
            char ci;
            scanf("%d %c", &fi, &ci);
            f[j][i] = fi;
            c_temp[j][i] = ci;
        }
    }
    
    // Initialize DP
    int dp_current[MAX_BULLETS+1];
    for(int b=0; b<=MAX_BULLETS; b++) dp_current[b] = INF;
    if(k <= MAX_BULLETS){
        dp_current[k] = 0;
    }
    
    // Process each column
    for(int j=0; j<m; j++){
        // Compute prefix sums for this column
        int sum_f[MAX_N+1];
        int sum_c[MAX_N+1];
        sum_f[0] = 0;
        sum_c[0] = 0;
        for(int t=1; t<=n; t++){
            sum_f[t] = sum_f[t-1] + f[j][t];
            sum_c[t] = sum_c[t-1] + (c_temp[j][t] == 'Y' ? 1 : 0);
        }
        
        // Initialize dp_next
        int dp_next[MAX_BULLETS+1];
        for(int b=0; b<=MAX_BULLETS; b++) dp_next[b] = INF;
        
        // Update dp_next based on current column
        for(int b=0; b<=MAX_BULLETS; b++){
            if(dp_current[b] != INF){
                for(int t=0; t<=n; t++){
                    int net_cost = t - sum_c[t];
                    if(net_cost <= b && net_cost >=0){
                        int new_b = b - net_cost;
                        if(new_b <= MAX_BULLETS){
                            if(dp_next[new_b] < dp_current[b] + sum_f[t]){
                                dp_next[new_b] = dp_current[b] + sum_f[t];
                            }
                        }
                    }
                }
            }
        }
        
        // Copy dp_next to dp_current
        for(int b=0; b<=MAX_BULLETS; b++) dp_current[b] = dp_next[b];
    }
    
    // Find the maximum score
    int max_score = 0;
    for(int b=0; b<=MAX_BULLETS; b++){
        if(dp_current[b] > max_score){
            max_score = dp_current[b];
        }
    }
    
    printf("%d", max_score);
    return 0;
}