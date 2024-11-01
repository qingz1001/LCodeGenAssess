#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int J;
    scanf("%d", &J);
    int apples[J];
    for(int i=0;i<J;i++) scanf("%d", &apples[i]);
    int pos_max = N - M +1;
    int prev_dp[pos_max+1];
    int curr_dp[pos_max+1];
    for(int p=1; p<=pos_max; p++) prev_dp[p] = (p ==1)? 0 : INF;
    for(int i=0;i<J;i++){
        int c = apples[i];
        for(int p=1; p<=pos_max; p++) curr_dp[p] = INF;
        int min_p = c - M +1;
        if(min_p <1) min_p =1;
        int max_p = c;
        if(max_p > pos_max) max_p = pos_max;
        for(int p = min_p; p <= max_p; p++){
            for(int p_prev=1; p_prev<=pos_max; p_prev++){
                if(prev_dp[p_prev] == INF) continue;
                int movement = abs(p - p_prev);
                int total = prev_dp[p_prev] + movement;
                if(total < curr_dp[p]) curr_dp[p] = total;
            }
        }
        for(int p=1; p<=pos_max; p++) prev_dp[p] = curr_dp[p];
    }
    int min_total = INF;
    for(int p=1; p<=pos_max; p++) if(prev_dp[p] < min_total) min_total = prev_dp[p];
    printf("%d\n", min_total);
    return 0;
}