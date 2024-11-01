#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_B 500
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int A, B;
int K[MAX_B][MAX_B];
int dp[1 << MAX_B];

int main() {
    scanf("%d %d", &A, &B);
    
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &K[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int mask = 1; mask < (1 << B); mask++) {
        for (int i = 0; i < B; i++) {
            if (mask & (1 << i)) {
                int prev_mask = mask ^ (1 << i);
                dp[mask] = MIN(dp[mask], dp[prev_mask] + A);
                
                for (int j = 0; j < B; j++) {
                    if (prev_mask & (1 << j)) {
                        dp[mask] = MIN(dp[mask], dp[prev_mask] + K[i][j]);
                    }
                }
            }
        }
    }
    
    printf("%d\n", dp[(1 << B) - 1]);
    
    return 0;
}