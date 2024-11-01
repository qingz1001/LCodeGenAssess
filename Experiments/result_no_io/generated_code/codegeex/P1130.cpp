#include <stdio.h>
#include <limits.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int days[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &days[i][j]);
        }
    }

    int dp[M][N];
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < M; i++) {
            if (i == 0) {
                dp[i][j] = days[i][j] + (j > 0 ? dp[M-1][j-1] : 0);
            } else {
                dp[i][j] = days[i][j] + (j > 0 ? min(dp[i-1][j-1], dp[i][j-1]) : dp[i-1][j-1]);
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < M; i++) {
        result = min(result, dp[i][N-1]);
    }

    printf("%d\n", result);
    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}