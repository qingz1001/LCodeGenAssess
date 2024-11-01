#include <stdio.h>
#include <string.h>

#define MAXN 500
#define MAXK 100

int dp[MAXN+1][MAXN+1][MAXK+1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, K;
    char sequence[MAXN+1];
    
    scanf("%d %d", &N, &K);
    scanf("%s", sequence);
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 0; k <= K; k++) {
                dp[i][j][k] = dp[i-1][j][k];
                if (sequence[i-1] == 'j') {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + (j > 0));
                } else {
                    if (k > 0) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k-1] + (j > 0));
                    }
                }
            }
        }
    }
    
    int result = 0;
    for (int k = 0; k <= K; k++) {
        result = max(result, dp[N][N][k]);
    }
    
    printf("%d\n", result);
    
    return 0;
}