#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 50
#define MAX_M 9

typedef struct {
    long long min;
    long long max;
} DPCell;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int list_orig[MAX_N];
    for(int i=0;i<n;i++) scanf("%d", &list_orig[i]);
    
    long long global_min = LLONG_MAX;
    long long global_max = LLONG_MIN;
    
    // Iterate over all possible starting positions
    for(int pos=0; pos<n; pos++){
        int list[MAX_N];
        for(int i=0;i<n;i++) list[i] = list_orig[(pos + i) % n];
        
        long long prefix[MAX_N+1];
        prefix[0] = 0;
        for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + list[i-1];
        
        // Initialize DP
        DPCell dp[MAX_M+1][MAX_N+1];
        for(int j=0; j<=m; j++) {
            for(int i=0; i<=n; i++) {
                dp[j][i].min = LLONG_MAX;
                dp[j][i].max = LLONG_MIN;
            }
        }
        
        for(int j=1; j<=m; j++){
            for(int i=j; i<=n; i++){
                if(j ==1){
                    long long sum_part = (prefix[i] - prefix[0]) % 10;
                    if(sum_part <0) sum_part = (sum_part +10 )%10;
                    dp[j][i].min = sum_part;
                    dp[j][i].max = sum_part;
                }
                else{
                    for(int k=j-1; k<=i-1; k++){
                        long long sum_part = (prefix[i] - prefix[k]) % 10;
                        if(sum_part <0) sum_part = (sum_part +10 )%10;
                        if(dp[j-1][k].min != LLONG_MAX){
                            long long temp_min = dp[j-1][k].min * sum_part;
                            if(temp_min < dp[j][i].min) dp[j][i].min = temp_min;
                        }
                        if(dp[j-1][k].max != LLONG_MIN){
                            long long temp_max = dp[j-1][k].max * sum_part;
                            if(temp_max > dp[j][i].max) dp[j][i].max = temp_max;
                        }
                    }
                }
            }
        }
        
        if(dp[m][n].min < global_min) global_min = dp[m][n].min;
        if(dp[m][n].max > global_max) global_max = dp[m][n].max;
    }
    
    printf("%lld\n%lld\n", global_min, global_max);
    return 0;
}