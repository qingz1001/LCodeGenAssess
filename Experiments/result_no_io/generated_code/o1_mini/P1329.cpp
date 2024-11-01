#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_N 100
#define OFFSET_A 100
#define OFFSET_S 10000
#define MAX_SUM 20001
#define MAX_A 201
#define MAX_S 20001
#define MAX_SEQUENCES 100

uint64_t dp[101][201][20001];
int a_min[101];
int a_max[101];
int n;
int target_s;
uint64_t total = 0;
int sequences_found = 0;
int sequences[MAX_SEQUENCES][100];

void initialize_dp() {
    memset(dp, 0, sizeof(dp));
    dp[1][OFFSET_A][OFFSET_S] = 1; // a1=0, sum=0
    for(int i=1;i<n;i++) {
        for(int a = a_min[i]; a <= a_max[i]; a++) {
            for(int s = -10000; s <= 10000; s++) {
                uint64_t cnt = dp[i][a + OFFSET_A][s + OFFSET_S];
                if(cnt == 0) continue;
                // Next step a+1
                int next_a = a + 1;
                int next_s = s + next_a;
                if(next_a < -100 || next_a > 100 || next_s < -10000 || next_s > 10000) {}
                else {
                    dp[i+1][next_a + OFFSET_A][next_s + OFFSET_S] += cnt;
                }
                // Next step a-1
                next_a = a -1;
                next_s = s + next_a;
                if(next_a < -100 || next_a > 100 || next_s < -10000 || next_s > 10000) {}
                else {
                    dp[i+1][next_a + OFFSET_A][next_s + OFFSET_S] += cnt;
                }
            }
        }
    }
    // Sum over a at step n with sum s
    for(int a = -100; a <= 100; a++) {
        if(target_s -0 < -10000 || target_s -0 > 10000) continue;
        total += dp[n][a + OFFSET_A][target_s + OFFSET_S];
    }
}

typedef struct {
    int seq[100];
} Sequence;

Sequence result_sequences[MAX_SEQUENCES];
int result_count = 0;

void backtrack(int step, int current_a, int current_sum, int *current_seq) {
    if(result_count >= MAX_SEQUENCES) return;
    if(step == n) {
        if(current_sum == target_s) {
            for(int i=0;i<n;i++) {
                sequences[result_count][i] = current_seq[i];
            }
            result_count++;
        }
        return;
    }
    // Try +1
    int next_a = current_a +1;
    int next_sum = current_sum + next_a;
    if(next_a >= -100 && next_a <= 100 && next_sum >= -10000 && next_sum <= 10000) {
        if(dp[n - step][next_a + OFFSET_A][next_sum + OFFSET_S] >0) {
            current_seq[step] = next_a;
            backtrack(step+1, next_a, next_sum, current_seq);
        }
    }
    // Try -1
    next_a = current_a -1;
    next_sum = current_sum + next_a;
    if(next_a >= -100 && next_a <= 100 && next_sum >= -10000 && next_sum <= 10000) {
        if(dp[n - step][next_a + OFFSET_A][next_sum + OFFSET_S] >0) {
            current_seq[step] = next_a;
            backtrack(step+1, next_a, next_sum, current_seq);
        }
    }
}

int main(){
    scanf("%d %d", &n, &target_s);
    // Initialize a_min and a_max
    a_min[1] = 0;
    a_max[1] = 0;
    for(int i=2;i<=n;i++) {
        a_min[i] = a_min[i-1] -1;
        a_max[i] = a_max[i-1] +1;
        if(a_min[i] < -100) a_min[i] = -100;
        if(a_max[i] > 100) a_max[i] = 100;
    }
    // Initialize dp
    memset(dp, 0, sizeof(dp));
    dp[1][0 + OFFSET_A][0 + OFFSET_S] = 1;
    for(int i=1;i<n;i++) {
        for(int a = a_min[i]; a <= a_max[i]; a++) {
            for(int s = -10000; s <= 10000; s++) {
                uint64_t cnt = dp[i][a + OFFSET_A][s + OFFSET_S];
                if(cnt == 0) continue;
                // Next step a+1
                int next_a = a + 1;
                int next_s = s + next_a;
                if(next_a >= -100 && next_a <= 100 && next_s >= -10000 && next_s <= 10000) {
                    dp[i+1][next_a + OFFSET_A][next_s + OFFSET_S] += cnt;
                }
                // Next step a-1
                next_a = a -1;
                next_s = s + next_a;
                if(next_a >= -100 && next_a <= 100 && next_s >= -10000 && next_s <= 10000) {
                    dp[i+1][next_a + OFFSET_A][next_s + OFFSET_S] += cnt;
                }
            }
        }
    }
    // Calculate total
    total = 0;
    for(int a = -100; a <= 100; a++) {
        int s = target_s;
        if(s < -10000 || s > 10000) continue;
        total += dp[n][a + OFFSET_A][s + OFFSET_S];
    }
    printf("%llu\n", total);
    if(total ==0){
        return 0;
    }
    // Backtrack to find sequences
    int current_seq[100];
    current_seq[0] = 0;
    backtrack(1, 0,0, current_seq);
    for(int i=0;i<result_count && i < MAX_SEQUENCES;i++) {
        for(int j=0;j<n;j++) {
            printf("%d%c", sequences[i][j], j==n-1? '\n':' ');
        }
    }
    return 0;
}