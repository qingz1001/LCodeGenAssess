#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_D 6000
#define OFFSET MAX_D
#define INF 1000000

int main(){
    int n;
    scanf("%d", &n);
    int a, b;
    // Initialize dp_prev
    int *dp_prev = (int*)malloc((2*MAX_D +1)*sizeof(int));
    int *dp_curr = (int*)malloc((2*MAX_D +1)*sizeof(int));
    for(int i=0;i<2*MAX_D+1;i++) dp_prev[i] = INF;
    dp_prev[OFFSET] = 0;
    
    for(int i=0;i<n;i++){
        scanf("%d %d", &a, &b);
        // Initialize dp_curr
        for(int j=0; j<2*MAX_D+1; j++) dp_curr[j] = INF;
        for(int d_prev =0; d_prev <2*MAX_D+1; d_prev++){
            if(dp_prev[d_prev] == INF) continue;
            // Option 1: not rotate
            int d1 = d_prev + (a - b);
            if(d1 >=0 && d1 <2*MAX_D+1){
                if(dp_curr[d1] > dp_prev[d_prev]){
                    dp_curr[d1] = dp_prev[d_prev];
                }
            }
            // Option 2: rotate
            int d2 = d_prev + (b - a);
            if(d2 >=0 && d2 <2*MAX_D+1){
                if(dp_curr[d2] > dp_prev[d_prev] +1){
                    dp_curr[d2] = dp_prev[d_prev] +1;
                }
            }
        }
        // Swap dp_prev and dp_curr
        int *temp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = temp;
    }
    // Find minimal |d|
    int min_diff = -1;
    int min_rot = INF;
    for(int d=0; d<=MAX_D; d++){
        // Check d and -d
        if(OFFSET + d <2*MAX_D+1){
            if(dp_prev[OFFSET + d] < INF){
                if(min_diff == -1 || d < min_diff || (d == min_diff && dp_prev[OFFSET + d] < min_rot)){
                    min_diff = d;
                    min_rot = dp_prev[OFFSET + d];
                }
            }
        }
        if(d !=0 && OFFSET - d >=0){
            if(dp_prev[OFFSET - d] < INF){
                if(min_diff == -1 || d < min_diff || (d == min_diff && dp_prev[OFFSET - d] < min_rot)){
                    min_diff = d;
                    min_rot = dp_prev[OFFSET - d];
                }
            }
        }
        if(min_diff != -1 && d > min_diff){
            break;
        }
    }
    printf("%d\n", min_rot);
    free(dp_prev);
    free(dp_curr);
    return 0;
}