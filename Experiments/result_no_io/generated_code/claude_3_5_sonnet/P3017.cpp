#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_R 500
#define MAX_C 500

int R, C, A, B;
int brownie[MAX_R][MAX_C];
int sum[MAX_R + 1][MAX_C + 1];
int dp[MAX_R + 1][MAX_C + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d %d", &R, &C, &A, &B);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf("%d", &brownie[i][j]);
        }
    }

    // Calculate prefix sum
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + brownie[i-1][j-1];
        }
    }

    // Initialize dp array
    for (int i = 0; i <= R; i++) {
        for (int j = 0; j <= C; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    // Dynamic programming
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (i * j < A * B) continue;

            int area = sum[i][j];
            dp[i][j] = area;

            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], max(dp[k][j], dp[i-k][j]));
            }

            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], max(dp[i][k], dp[i][j-k]));
            }
        }
    }

    printf("%d\n", dp[R][C]);

    return 0;
}