#include <stdio.h>
#include <stdlib.h>

#define MAXN 201

int dp[MAXN][MAXN];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &dp[m-1][i]);
    }

    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                dp[i][j] += max(dp[i+1][j], dp[i+1][j+1]);
            } else if (j == n-1) {
                dp[i][j] += max(dp[i+1][j], dp[i+1][j-1]);
            } else {
                dp[i][j] += max(max(dp[i+1][j], dp[i+1][j+1]), dp[i+1][j-1]);
            }
        }
    }

    int max_energy = dp[0][n/2];
    printf("%d\n", max_energy);

    return 0;
}