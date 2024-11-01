#include <stdio.h>
#include <limits.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Define maximum sizes based on constraints
    int days[M][N];
    
    // Read the days matrix
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &days[i][j]);
        }
    }
    
    // Initialize previous and current DP arrays
    long long prev_dp[M];
    long long curr_dp[M];
    
    // Initialize for the first step
    for(int i=0;i<M;i++){
        prev_dp[i] = days[i][0];
    }
    
    // Iterate through each step
    for(int step=1; step<N; step++){
        for(int g=0; g<M; g++){
            int prev_group = (g - 1 + M) % M;
            long long option1 = prev_dp[g];
            long long option2 = prev_dp[prev_group];
            if(option1 < option2){
                curr_dp[g] = option1 + days[g][step];
            }
            else{
                curr_dp[g] = option2 + days[g][step];
            }
        }
        // Swap current and previous
        for(int g=0; g<M; g++) prev_dp[g] = curr_dp[g];
    }
    
    // Find the minimum in the last step
    long long min_total = LLONG_MAX;
    for(int i=0;i<M;i++){
        if(prev_dp[i] < min_total){
            min_total = prev_dp[i];
        }
    }
    
    printf("%lld", min_total);
    return 0;
}