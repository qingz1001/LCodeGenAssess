#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2001
#define MAX_M 2001
#define INF 0x3f3f3f3f

int N, M;
int cost[MAX_M][MAX_N];
int dp[MAX_M][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    
    for (int i = 0; i < M; i++) {
        dp[i][0] = cost[i][0];
    }
    
    for (int j = 1; j < N; j++) {
        for (int i = 0; i < M; i++) {
            for (int k = 0; k < M; k++) {
                int prev = (i - k + M) % M;
                dp[i][j] = min(dp[i][j], dp[prev][j-1] + cost[i][j]);
            }
        }
    }
    
    int result = INF;
    for (int i = 0; i < M; i++) {
        result = min(result, dp[i][N-1]);
    }
    
    printf("%d\n", result);
    
    return 0;
}