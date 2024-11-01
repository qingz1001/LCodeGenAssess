#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000

int main(){
    int N, M, J;
    scanf("%d %d", &N, &M);
    scanf("%d", &J);
    int apples[J];
    for(int i=0;i<J;i++) scanf("%d", &apples[i]);
    
    int max_p = N - M +1;
    // Initialize DP arrays
    int prev_dp[max_p+1];
    int curr_dp[max_p+1];
    for(int p=1;p<=max_p;p++) prev_dp[p] = INF;
    prev_dp[1] = 0; // initial position is 1
    
    for(int i=0;i<J;i++){
        // Initialize current dp to INF
        for(int p=1;p<=max_p;p++) curr_dp[p] = INF;
        int ai = apples[i];
        for(int p=1;p<=max_p;p++){
            // Check if p covers ai
            if(ai >= p && ai <= p + M -1){
                for(int p_prev=1;p_prev<=max_p;p_prev++){
                    if(prev_dp[p_prev] < INF){
                        int move = abs(p - p_prev);
                        if(prev_dp[p_prev] + move < curr_dp[p]){
                            curr_dp[p] = prev_dp[p_prev] + move;
                        }
                    }
                }
            }
        }
        // Copy current dp to previous dp
        for(int p=1;p<=max_p;p++) prev_dp[p] = curr_dp[p];
    }
    
    // Find minimum in prev_dp
    int min_total = INF;
    for(int p=1;p<=max_p;p++) if(prev_dp[p] < min_total) min_total = prev_dp[p];
    
    printf("%d\n", min_total);
}