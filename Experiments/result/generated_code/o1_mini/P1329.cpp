#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_SEQ 100
#define OFFSET 10000
#define LAST_RANGE 201
#define SUM_RANGE 20001

unsigned long long dp_current[LAST_RANGE][SUM_RANGE];
unsigned long long dp_next[LAST_RANGE][SUM_RANGE];
unsigned long long total = 0;

int n;
long long s;

// Sequences storage
int sequences_collected = 0;
int sequences[MAX_SEQ][MAX_N];

// Backtracking
void backtrack(int step, int last, long long current_sum, int *seq) {
    if (sequences_collected >= MAX_SEQ) return;
    if (step == n) {
        if (current_sum == s) {
            memcpy(sequences[sequences_collected], seq, sizeof(int)*n);
            sequences_collected++;
        }
        return;
    }
    // Try -1
    int next_val = last - 1;
    long long next_sum = current_sum + next_val;
    if (next_val >= -100 && next_val <= 100) { // Value constraints
        // Check if possible
        // Estimate remaining sum range
        int remaining = n - step -1;
        long long min_sum = next_sum + (long long)(-100) * (n - step -1);
        long long max_sum = next_sum + (long long)(100) * (n - step -1);
        if (s >= min_sum && s <= max_sum) {
            seq[step] = next_val;
            backtrack(step +1, next_val, next_sum, seq);
        }
    }
    // Try +1
    next_val = last +1;
    next_sum = current_sum + next_val;
    if (next_val >= -100 && next_val <= 100) { // Value constraints
        // Check if possible
        int remaining = n - step -1;
        long long min_sum = next_sum + (long long)(-100) * (n - step -1);
        long long max_sum = next_sum + (long long)(100) * (n - step -1);
        if (s >= min_sum && s <= max_sum) {
            seq[step] = next_val;
            backtrack(step +1, next_val, next_sum, seq);
        }
    }
}

int main(){
    scanf("%d %lld", &n, &s);
    memset(dp_current, 0, sizeof(dp_current));
    // Initialize
    dp_current[100][OFFSET] = 1;
    for(int step=1; step<n; step++){
        memset(dp_next, 0, sizeof(dp_next));
        for(int last=0; last<LAST_RANGE; last++){
            for(int sum_idx=0; sum_idx<SUM_RANGE; sum_idx++){
                if(dp_current[last][sum_idx] == 0) continue;
                // Try -1
                int new_last = last -100;
                new_last = (last - 100) + (-1);
                int actual_last = last - 100;
                int next_val = actual_last -1;
                if(next_val >= -100 && next_val <=100){
                    int next_last = next_val + 100;
                    long long new_sum = (sum_idx - OFFSET) + next_val;
                    if(new_sum + OFFSET >=0 && new_sum + OFFSET < SUM_RANGE){
                        dp_next[next_last][new_sum + OFFSET] += dp_current[last][sum_idx];
                    }
                }
                // Try +1
                next_val = actual_last +1;
                if(next_val >= -100 && next_val <=100){
                    int next_last = next_val + 100;
                    long long new_sum = (sum_idx - OFFSET) + next_val;
                    if(new_sum + OFFSET >=0 && new_sum + OFFSET < SUM_RANGE){
                        dp_next[next_last][new_sum + OFFSET] += dp_current[last][sum_idx];
                    }
                }
            }
        }
        // Swap
        memcpy(dp_current, dp_next, sizeof(dp_current));
    }
    // Count total
    total =0;
    for(int last=0; last<LAST_RANGE; last++){
        long long sum = s;
        if(sum + OFFSET <0 || sum + OFFSET >= SUM_RANGE) continue;
        total += dp_current[last][sum + OFFSET];
    }
    printf("%llu\n", total);
    if(total >0){
        // Backtrack to collect sequences
        int seq[MAX_N];
        seq[0] =0;
        backtrack(1, 0, 0, seq);
        for(int i=0; i<sequences_collected; i++){
            for(int j=0; j<n; j++){
                if(j>0) printf(" ");
                printf("%d", sequences[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}