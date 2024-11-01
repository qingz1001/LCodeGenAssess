#include <stdio.h>
#include <string.h>

#define MAX_N 15
#define MAX_K 15
#define MAX_VALUE 10000

int N, K;
int stamps[MAX_K];
int dp[MAX_VALUE];
int best_stamps[MAX_K];
int max_value;

void dfs(int depth, int last) {
    if (depth == K) {
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int current_max = 0;
        
        for (int i = 0; i < MAX_VALUE; i++) {
            if (dp[i]) {
                current_max = i;
                for (int j = 0; j < K && i + stamps[j] < MAX_VALUE; j++) {
                    if (dp[i] <= N) {
                        dp[i + stamps[j]] = 1;
                    }
                }
            } else {
                break;
            }
        }
        
        if (current_max > max_value) {
            max_value = current_max;
            memcpy(best_stamps, stamps, sizeof(stamps));
        }
        return;
    }
    
    for (int i = last + 1; i < MAX_VALUE; i++) {
        stamps[depth] = i;
        dfs(depth + 1, i);
    }
}

int main() {
    scanf("%d %d", &N, &K);
    
    stamps[0] = 1;
    dfs(1, 1);
    
    for (int i = 0; i < K; i++) {
        printf("%d ", best_stamps[i]);
    }
    printf("\nMAX=%d\n", max_value);
    
    return 0;
}