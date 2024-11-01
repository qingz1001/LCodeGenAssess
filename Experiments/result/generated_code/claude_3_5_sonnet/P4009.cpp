#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define MAX_K 10

int N, K, A, B, C;
int oil[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_K+1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &A, &B, &C);
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &oil[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][K] = 0;
    
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k <= K; k++) {
                if(dp[i][j][k] == 0x3f3f3f3f) continue;
                
                if(i+1 < N) {
                    if(k > 0) {
                        dp[i+1][j][k-1] = min(dp[i+1][j][k-1], dp[i][j][k]);
                    }
                    if(oil[i+1][j]) {
                        dp[i+1][j][K] = min(dp[i+1][j][K], dp[i][j][k] + A);
                    }
                    dp[i+1][j][K] = min(dp[i+1][j][K], dp[i][j][k] + C + A);
                }
                
                if(j+1 < N) {
                    if(k > 0) {
                        dp[i][j+1][k-1] = min(dp[i][j+1][k-1], dp[i][j][k]);
                    }
                    if(oil[i][j+1]) {
                        dp[i][j+1][K] = min(dp[i][j+1][K], dp[i][j][k] + A);
                    }
                    dp[i][j+1][K] = min(dp[i][j+1][K], dp[i][j][k] + C + A);
                }
            }
        }
    }
    
    int result = INT_MAX;
    for(int k = 0; k <= K; k++) {
        result = min(result, dp[N-1][N-1][k]);
    }
    
    printf("%d\n", result);
    
    return 0;
}