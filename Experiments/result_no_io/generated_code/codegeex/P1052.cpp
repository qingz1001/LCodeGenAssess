#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, S, T, M;
    scanf("%d", &L);
    scanf("%d%d%d", &S, &T, &M);
    
    int *stones = (int*)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        scanf("%d", &stones[i]);
    }
    
    // Sort the stones array
    for (int i = 0; i < M - 1; i++) {
        for (int j = i + 1; j < M; j++) {
            if (stones[i] > stones[j]) {
                int temp = stones[i];
                stones[i] = stones[j];
                stones[j] = temp;
            }
        }
    }
    
    // Initialize the dp array
    int *dp = (int*)calloc(L + 1, sizeof(int));
    
    // Mark the positions of stones
    for (int i = 0; i < M; i++) {
        dp[stones[i]] = 1;
    }
    
    // Dynamic programming to find the minimum number of stones to step on
    for (int i = S; i <= T; i++) {
        for (int j = i; j <= L; j++) {
            if (j >= i) {
                dp[j] += dp[j - i];
            }
        }
    }
    
    // Find the minimum number of stones to step on to reach the end
    int min_stones = dp[L];
    
    // Output the result
    printf("%d\n", min_stones);
    
    // Free the allocated memory
    free(stones);
    free(dp);
    
    return 0;
}