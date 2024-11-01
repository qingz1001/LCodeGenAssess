#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200

int max(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

int main() {
    int m, n;
    int table[MAX_SIZE][MAX_SIZE];
    int dp[MAX_SIZE][MAX_SIZE];

    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &table[i][j]);
        }
    }

    for (int j = 0; j < n; j++) {
        dp[0][j] = table[0][j];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j+1], -1000000) + table[i][j];
            } else if (j == n-1) {
                dp[i][j] = max(dp[i-1][j-1], dp[i-1][j], -1000000) + table[i][j];
            } else {
                dp[i][j] = max(dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1]) + table[i][j];
            }
        }
    }

    int result = dp[m-1][n/2];
    printf("%d\n", result);

    return 0;
}