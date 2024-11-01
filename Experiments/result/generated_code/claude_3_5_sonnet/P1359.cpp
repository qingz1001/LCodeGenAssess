#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 200

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    int r[MAX_N][MAX_N] = {0};
    int dp[MAX_N] = {0};

    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &r[i][j]);
        }
    }

    for (int i = 2; i <= n; i++) {
        dp[i] = r[1][i];
        for (int j = 2; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + r[j][i]);
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}