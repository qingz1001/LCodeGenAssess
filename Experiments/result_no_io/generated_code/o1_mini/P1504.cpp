#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_EDGE 100
#define MAX_SUM 10000

unsigned char dp_prev[101][10001];
unsigned char dp_current[101][10001];
unsigned char castle_possible[10001];
unsigned char global_possible_arr[10001];

int main(){
    int n;
    scanf("%d", &n);
    
    // Initialize global_possible to 1 for all sums
    for(int h=0; h<=MAX_SUM; h++) {
        global_possible_arr[h] = 1;
    }
    
    for(int castle=0; castle < n; castle++){
        int blocks[MAX_BLOCKS];
        int bc = 0;
        while(1){
            int x;
            scanf("%d", &x);
            if(x == -1) break;
            blocks[bc++] = x;
        }
        
        // Initialize dp_prev
        memset(dp_prev, 0, sizeof(dp_prev));
        dp_prev[MAX_EDGE][0] = 1;
        
        // Process each block
        for(int b=0; b < bc; b++){
            int block = blocks[b];
            memset(dp_current, 0, sizeof(dp_current));
            
            for(int last_edge=0; last_edge <= MAX_EDGE; last_edge++){
                for(int sum=0; sum <= MAX_SUM; sum++){
                    if(dp_prev[last_edge][sum]){
                        // Don't take the block
                        if(!dp_current[last_edge][sum]){
                            dp_current[last_edge][sum] = 1;
                        }
                        // Take the block if possible
                        if(block <= last_edge){
                            int new_last = block;
                            int new_sum = sum + block;
                            if(new_sum <= MAX_SUM){
                                if(!dp_current[new_last][new_sum]){
                                    dp_current[new_last][new_sum] = 1;
                                }
                            }
                        }
                    }
                }
            }
            // Swap dp_prev and dp_current
            memcpy(dp_prev, dp_current, sizeof(dp_prev));
        }
        
        // Collect castle_possible
        memset(castle_possible, 0, sizeof(castle_possible));
        for(int last_edge=0; last_edge <= MAX_EDGE; last_edge++){
            for(int sum=0; sum <= MAX_SUM; sum++){
                if(dp_prev[last_edge][sum]){
                    castle_possible[sum] = 1;
                }
            }
        }
        
        // Update global_possible
        for(int h=0; h <= MAX_SUM; h++){
            global_possible_arr[h] &= castle_possible[h];
        }
    }
    
    // Find the maximum possible height
    int max_h = 0;
    for(int h = MAX_SUM; h >=0; h--){
        if(global_possible_arr[h]){
            max_h = h;
            break;
        }
    }
    
    printf("%d\n", max_h);
    return 0;
}