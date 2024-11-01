#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20001
#define MAX_K 101
#define INF 0x3f3f3f3f

int N, K;
int D[MAX_N], C[MAX_N], S[MAX_N], W[MAX_N];
int dp[MAX_N][MAX_K];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &K);
    
    D[1] = 0;
    for (int i = 2; i <= N; i++) {
        scanf("%d", &D[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
    }
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if (j > 0) {
                int cost = C[i];
                for (int k = i; k >= 1 && D[i] - D[k] <= S[i]; k--) {
                    dp[i][j] = min(dp[i][j], dp[k-1][j-1] + cost);
                }
            }
            
            int penalty = 0;
            for (int k = i; k >= 1 && D[i] - D[k] <= S[k]; k--) {
                dp[i][j] = min(dp[i][j], dp[k-1][j] + penalty);
                penalty += W[k];
            }
        }
    }
    
    int result = INF;
    for (int j = 0; j <= K; j++) {
        result = min(result, dp[N][j]);
    }
    
    printf("%d\n", result);
    
    return 0;
}