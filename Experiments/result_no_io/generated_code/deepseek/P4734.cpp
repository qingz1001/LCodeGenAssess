#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int dp[MAXN][MAXN];
int values[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    // Initialize dp array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MIN;
        }
    }

    // Base case: Byteasar hacks the first computer
    for (int i = 0; i < n; i++) {
        dp[i][(i + 1) % n] = values[i];
    }

    // Fill dp array
    for (int len = 2; len < n; len++) {
        for (int i = 0; i < n; i++) {
            int j = (i + len) % n;
            int k = (i + 1) % n;
            dp[i][j] = max(dp[i][j], dp[i][k] + values[(k + 1) % n]);
            k = (i + len - 1) % n;
            dp[i][j] = max(dp[i][j], dp[k][j] + values[(k - 1 + n) % n]);
        }
    }

    // Find the maximum score
    int max_score = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + n - 1) % n;
        max_score = max(max_score, dp[i][j]);
    }

    printf("%d\n", max_score);

    return 0;
}