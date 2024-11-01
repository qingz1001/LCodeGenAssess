#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25
#define MAX_H 16

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, h, f[MAX_N], d[MAX_N], t[MAX_N];
    scanf("%d %d", &n, &h);
    for (int i = 0; i < n; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &t[i]);
    }

    int dp[MAX_N][MAX_H * 60 + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= MAX_H * 60; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= MAX_H * 60; j++) {
            if (j >= 5 * t[i - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 5 * t[i - 1]] + f[i - 1]);
                for (int k = 1; k * 5 <= j - 5 * t[i - 1]; k++) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 5 * t[i - 1] - k * 5] + f[i - 1] - k * d[i - 1]);
                }
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int result = 0;
    for (int i = 0; i <= MAX_H * 60; i++) {
        result = max(result, dp[n][i]);
    }

    printf("%d\n", result);

    return 0;
}