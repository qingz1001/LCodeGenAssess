#include <stdio.h>
#include <stdlib.h>

#define MAX_M 6
#define MAX_MASK (1<<MAX_M)
#define MAX_N 6
#define MAX_T 20

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N, M;
        scanf("%d %d", &N, &M);
        int grid[MAX_N][MAX_M];
        for(int i=0;i<N;i++) {
            for(int j=0;j<M;j++) {
                scanf("%d", &grid[i][j]);
            }
        }
        // Precompute sums for each row and mask
        int sum[MAX_N][MAX_MASK];
        for(int i=0;i<N;i++) {
            for(int mask=0; mask<(1<<M); mask++) {
                // Check no two adjacent bits
                if( (mask & (mask >>1)) !=0 ) {
                    sum[i][mask] = -1;
                    continue;
                }
                int valid = 1;
                for(int j=0; j<M; j++) {
                    if(mask & (1<<j)) {
                        // No need to check within the same row as already checked
                        // Just accumulate the sum
                        // As numbers are non-negative, no need to check anything else
                        // Continue
                    }
                }
                if(sum[i][mask]!=-1){
                    int s =0;
                    for(int j=0; j<M; j++) {
                        if(mask & (1<<j)) s += grid[i][j];
                    }
                    sum[i][mask] = s;
                }
            }
        }
        // Initialize DP
        long long prev_dp[MAX_MASK];
        for(int mask=0; mask<(1<<M); mask++) {
            if(sum[0][mask] != -1){
                prev_dp[mask] = sum[0][mask];
            }
            else{
                prev_dp[mask] = -1;
            }
        }
        // Iterate through rows
        for(int i=1;i<N;i++) {
            long long current_dp[MAX_MASK];
            for(int mask=0; mask<(1<<M); mask++) {
                current_dp[mask] = -1;
            }
            for(int curr=0; curr<(1<<M); curr++) {
                if(sum[i][curr]==-1) continue;
                for(int prev=0; prev<(1<<M); prev++) {
                    if(prev_dp[prev]==-1) continue;
                    // Check compatibility
                    // No adjacent including diagonals
                    if( (curr & prev) ) continue;
                    if( (curr & (prev <<1)) ) continue;
                    if( (curr & (prev >>1)) ) continue;
                    long long temp = prev_dp[prev] + sum[i][curr];
                    if(temp > current_dp[curr]){
                        current_dp[curr] = temp;
                    }
                }
            }
            // Update prev_dp
            for(int mask=0; mask<(1<<M); mask++) {
                prev_dp[mask] = current_dp[mask];
            }
        }
        // Find maximum
        long long max_sum =0;
        for(int mask=0; mask<(1<<M); mask++) {
            if(prev_dp[mask] > max_sum){
                max_sum = prev_dp[mask];
            }
        }
        printf("%lld\n", max_sum);
    }
    return 0;
}