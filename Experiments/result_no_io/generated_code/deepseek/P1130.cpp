#include <stdio.h>
#include <limits.h>

#define MAXN 2000
#define MAXM 2000

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int days[MAXM][MAXN];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &days[i][j]);
        }
    }

    int dp[MAXM][MAXN];
    for (int i = 0; i < M; i++) {
        dp[i][0] = days[i][0];
    }

    for (int j = 1; j < N; j++) {
        for (int i = 0; i < M; i++) {
            dp[i][j] = INT_MAX;
            for (int k = 0; k < M; k++) {
                int cost = dp[k][j-1];
                if (k != i) {
                    cost += days[i][j];
                } else {
                    cost += days[i][j];
                }
                dp[i][j] = min(dp[i][j], cost);
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