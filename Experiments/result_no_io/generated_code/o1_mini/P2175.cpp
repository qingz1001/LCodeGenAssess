#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define WORD_SIZE 64
#define MAX_BITS ((MAX_N / WORD_SIZE) + 1)

// Function to set a bit in the bitmask
void set_bit(unsigned long long *mask, int pos) {
    mask[pos / WORD_SIZE] |= 1ULL << (pos % WORD_SIZE);
}

// Function to check if a bit is set in the bitmask
int is_bit_set(unsigned long long *mask, int pos) {
    return (mask[pos / WORD_SIZE] & (1ULL << (pos % WORD_SIZE))) != 0;
}

// Function to shift mask left by shift bits
void shift_left(unsigned long long *src, unsigned long long *dst, int shift, int num_words) {
    memset(dst, 0, sizeof(unsigned long long) * num_words);
    int word_shift = shift / WORD_SIZE;
    int bit_shift = shift % WORD_SIZE;
    for(int i = num_words -1; i >=0; i--){
        if(i - word_shift <0) continue;
        dst[i] |= src[i - word_shift] << bit_shift;
        if(bit_shift !=0 && (i - word_shift -1)>=0){
            dst[i] |= src[i - word_shift -1] >> (WORD_SIZE - bit_shift);
        }
    }
}

// Function to OR two masks
void or_mask(unsigned long long *a, unsigned long long *b, unsigned long long *res, int num_words){
    for(int i=0;i<num_words;i++) res[i] = a[i] | b[i];
}

int main(){
    int N;
    scanf("%d", &N);
    // Initialize trust lists
    unsigned char trust[MAX_N][MAX_N];
    memset(trust, 0, sizeof(trust));
    for(int i=0;i<N;i++){
        int y;
        while(scanf("%d", &y) && y !=0){
            if(y >=1 && y <=N){
                trust[i][y-1] = 1;
            }
        }
    }
    // Build mutual connections
    unsigned long long mutual[MAX_N];
    memset(mutual, 0, sizeof(mutual));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) {
            if(i != j && trust[i][j] && trust[j][i]){
                mutual[i] |= 1ULL << j;
            }
        }
    }
    // BFS to check bipartiteness and collect component sizes
    int color[MAX_N];
    memset(color, -1, sizeof(color));
    int queue[MAX_N];
    int head, tail;
    int possible = 1;
    // To store component sizes
    int comp_sizes0[MAX_N];
    int comp_sizes1[MAX_N];
    int comp_cnt =0;
    for(int i=0;i<N && possible;i++){
        if(color[i]==-1){
            color[i]=0;
            head=0; tail=0;
            queue[tail++] = i;
            int cnt0=1, cnt1=0;
            while(head < tail && possible){
                int u = queue[head++];
                for(int v=0; v<N && possible; v++){
                    if(u == v) continue;
                    // If not mutually connected, it's a complement edge
                    if( !(mutual[u] & (1ULL << v)) ){
                        if(color[v]==-1){
                            color[v] = 1 - color[u];
                            if(color[v]==0) cnt0++;
                            else cnt1++;
                            queue[tail++] = v;
                        }
                        else{
                            if(color[v] != 1 - color[u]){
                                possible =0;
                            }
                        }
                    }
                }
            }
            if(possible){
                comp_sizes0[comp_cnt] = cnt0;
                comp_sizes1[comp_cnt] = cnt1;
                comp_cnt++;
            }
        }
    }
    if(!possible){
        printf("No solution\n");
        return 0;
    }
    // DP for subset sum
    int num_words = (N / WORD_SIZE) +1;
    unsigned long long dp_current[MAX_BITS];
    unsigned long long dp_next[MAX_BITS];
    memset(dp_current, 0, sizeof(unsigned long long)*MAX_BITS);
    set_bit(dp_current, 0);
    for(int c=0;c<comp_cnt;c++){
        unsigned long long shift1[MAX_BITS], shift2[MAX_BITS];
        memset(shift1, 0, sizeof(unsigned long long)*MAX_BITS);
        memset(shift2, 0, sizeof(unsigned long long)*MAX_BITS);
        // Shift by size0
        shift_left(dp_current, shift1, comp_sizes0[c], MAX_BITS);
        // Shift by size1
        shift_left(dp_current, shift2, comp_sizes1[c], MAX_BITS);
        // OR the two
        or_mask(shift1, shift2, dp_next, MAX_BITS);
        // Update dp_current
        memcpy(dp_current, dp_next, sizeof(unsigned long long)*MAX_BITS);
    }
    // Find the best size_A
    int best_diff = N+1;
    int best_A = -1;
    for(int s=0;s<=N;s++) {
        if(is_bit_set(dp_current, s)){
            int diff = abs((N - s) - s);
            if(diff < best_diff){
                best_diff = diff;
                best_A = s;
            }
        }
    }
    if(best_A == -1){
        printf("No solution\n");
        return 0;
    }
    int size_A = best_A;
    int size_B = N - best_A;
    if(size_A <= size_B){
        printf("%d %d\n", size_A, size_B);
    }
    else{
        printf("%d %d\n", size_B, size_A);
    }
    return 0;
}