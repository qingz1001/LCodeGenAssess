#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, K;
    if(scanf("%d %d", &N, &K)!=2){
        return 0;
    }
    // Calculate desired starting positions
    long long *desired_pos = (long long*)calloc(N+1, sizeof(long long));
    int *S = (int*)malloc((K+1)*sizeof(int));
    int i, j, block;
    long long P = 1;
    for(i=1;i<=K;i++){
        scanf("%d", &S[i]);
        for(j=0;j<S[i];j++){
            scanf("%d", &block);
            desired_pos[block] = P + j;
        }
        P += S[i];
    }
    // Collect sequence of desired positions in disk order
    // Disk blocks are from 1 to N
    // Assuming disk blocks are arranged from 1 to N
    // So iterate from 1 to N
    // If a block is occupied, add its desired position to sequence
    // Also count total occupied blocks
    int *sequence = (int*)malloc(N * sizeof(int));
    int seq_len = 0;
    for(i=1;i<=N;i++){
        if(desired_pos[i]!=0){
            sequence[seq_len++] = desired_pos[i];
        }
    }
    // Find LIS
    // Using tail array
    int *tail = (int*)malloc(seq_len * sizeof(int));
    int tail_len = 0;
    for(i=0;i<seq_len;i++){
        int x = sequence[i];
        int l=0, r=tail_len;
        while(l < r){
            int m = l + (r - l)/2;
            if(tail[m] < x){
                l = m +1;
            }
            else{
                r = m;
            }
        }
        tail[l] = x;
        if(l == tail_len){
            tail_len++;
        }
    }
    int M = seq_len - tail_len;
    if(M == 0){
        printf("No optimization needed.\n");
    }
    else{
        printf("We need %d move operations.\n", M);
    }
    // Free memory
    free(desired_pos);
    free(S);
    free(sequence);
    free(tail);
    return 0;
}