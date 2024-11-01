#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXR 500
#define MAXC 500

int R, C, A, B;
int brownie[MAXR+1][MAXC+1];
int sum[MAXR+1][MAXC+1];
int dp[MAXR+1][MAXC+1];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void preprocess() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + brownie[i][j];
        }
    }
}

int getSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int solve() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            dp[i][j] = INT_MAX;
            for (int k = 1; k <= B; k++) {
                int cur = getSum(1, j-k+1, i, j);
                if (j-k >= 0) {
                    cur = min(cur, dp[i][j-k]);
                }
                dp[i][j] = min(dp[i][j], cur);
            }
        }
    }

    int result = 0;
    for (int i = A; i <= R; i++) {
        result = max(result, dp[i][C] - dp[i-A][C]);
    }
    return result;
}

int main() {
    scanf("%d %d %d %d", &R, &C, &A, &B);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &brownie[i][j]);
        }
    }

    preprocess();
    printf("%d\n", solve());

    return 0;
}