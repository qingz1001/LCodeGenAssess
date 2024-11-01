#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_C 5000
#define MAX_S 100

int main() {
    int N, S;
    scanf("%d %d", &N, &S);
    
    int C[MAX_N], Y[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &C[i], &Y[i]);
    }
    
    long long dp[MAX_N][MAX_Y + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            dp[i][j] = (long long)MAX_N * MAX_C * MAX_S; // Initialize to a large value
        }
    }
    
    dp[0][0] = 0;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= MAX_Y; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] = fmin(dp[i][j], dp[i - 1][j - k] + (long long)k * S + (long long)(C[i - 1] * (j - k)));
            }
        }
    }
    
    printf("%lld\n", dp[N][MAX_Y]);
    
    return 0;
}