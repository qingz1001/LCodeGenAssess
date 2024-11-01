#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_M 2000
#define INF 1000000000

int N, M;
int days[MAX_M][MAX_N];
int dp[MAX_M][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &days[i][j]);
        }
    }

    // Initialize first column of dp
    for (int i = 0; i < M; i++) {
        dp[i][0] = days[i][0];
    }

    // Fill dp table
    for (int j = 1; j < N; j++) {
        for (int i = 0; i < M; i++) {
            dp[i][j] = INF;
            for (int k = 0; k < M; k++) {
                int prev = dp[k][j-1];
                if (k != i) {
                    prev += (i - k + M) % M; // Cost of switching groups
                }
                dp[i][j] = min(dp[i][j], prev + days[i][j]);
            }
        }
    }

    // Find minimum in last column
    int result = INF;
    for (int i = 0; i < M; i++) {
        result = min(result, dp[i][N-1]);
    }

    printf("%d\n", result);

    return 0;
}