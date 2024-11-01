#include <stdio.h>

#define MOD 9901

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (n != (1 << k) - 1) {
        printf("0\n");
        return 0;
    }

    int dp[k + 1][n + 1];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][1] = 1;

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= (1 << i); j++) {
            dp[i][j] = (dp[i-1][j/2] * 2) % MOD;
        }
    }

    printf("%d\n", dp[k][n]);

    return 0;
}