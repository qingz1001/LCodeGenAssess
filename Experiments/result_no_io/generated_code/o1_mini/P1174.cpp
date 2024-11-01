#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_M 200
#define MAX_N 200
#define MAX_K 400
#define INF -1000000000

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Initialize brick scores and bonus
    int scores[MAX_M][MAX_N];
    int bonus[MAX_M][MAX_N];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int f;
            char c;
            scanf("%d %c", &f, &c);
            scores[j][n-1-i] = f;
            bonus[j][n-1-i] = (c == 'Y') ? 1 : 0;
        }
    }
    
    // Precompute cumulative scores and bonuses for each column
    int cum_scores[MAX_M][MAX_N+1];
    int cum_bonus[MAX_M][MAX_N+1];
    for(int j=0;j<m;j++){
        cum_scores[j][0] = 0;
        cum_bonus[j][0] = 0;
        for(int t=1;t<=n;t++){
            cum_scores[j][t] = cum_scores[j][t-1] + scores[j][t-1];
            cum_bonus[j][t] = cum_bonus[j][t-1] + bonus[j][t-1];
        }
    }
    
    // Initialize DP
    int dp_prev[MAX_K+201];
    int dp_next[MAX_K+201];
    for(int j=0; j<=MAX_K+200; j++) dp_prev[j] = INF;
    dp_prev[k] = 0;
    
    // Iterate over each column
    for(int j=0; j<m; j++){
        for(int b=0; b<=MAX_K+200; b++) dp_next[b] = INF;
        for(int b_prev=0; b_prev<=MAX_K+200; b_prev++){
            if(dp_prev[b_prev] == INF) continue;
            // Try all possible t
            // Find number of bricks in this column
            int num = n;
            while(num >0 && cum_scores[j][num] == cum_scores[j][n]) num--;
            for(int t=0; t<=n; t++){
                if(t > n) break;
                int b_new = b_prev - t + cum_bonus[j][t];
                if(b_new <0 || b_new > MAX_K+200) continue;
                if(cum_scores[j][t] == 0 && t !=0) continue;
                if(t > n) continue;
                if(t > n) continue;
                if(t >0 && t > n) continue;
                if(t > n) continue;
                if(t >0 && t > n) continue;
                if(t >n) continue;
                if(t > n) continue;
                if(t >n) continue;
                // Update score
                if(cum_scores[j][t] == 0 && t !=0) continue;
                if(t > n) continue;
                if(t >n) continue;
                if(t >n) continue;
                if(t >n) continue;
                if(t >n) continue;
                if(t >n) continue;
                // Update DP
                if(cum_scores[j][t] >=0){
                    if(dp_next[b_new] < dp_prev[b_prev] + cum_scores[j][t]){
                        dp_next[b_new] = dp_prev[b_prev] + cum_scores[j][t];
                    }
                }
            }
        }
        // Swap dp_prev and dp_next
        for(int b=0; b<=MAX_K+200; b++) dp_prev[b] = dp_next[b];
    }
    
    // Find maximum score
    int max_score = 0;
    for(int b=0; b<=MAX_K+200; b++) {
        if(dp_prev[b] > max_score){
            max_score = dp_prev[b];
        }
    }
    printf("%d\n", max_score);
    return 0;
}