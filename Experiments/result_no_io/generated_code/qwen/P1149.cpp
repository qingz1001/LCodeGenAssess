#include <stdio.h>
#include <stdlib.h>

int matchsticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int count_ways(int n) {
    int dp[n + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j >= matchsticks[i - 1]) {
                dp[i][j] += dp[i - 1][j - matchsticks[i - 1]];
            }
            dp[i][j] += dp[i - 1][j];
        }
    }

    int result = 0;
    for (int a = 1; a <= n / 2; a++) {
        for (int b = 1; b <= n / 2; b++) {
            int c = n - a - b;
            if (a + b == c && a != b) {
                result++;
            }
        }
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", count_ways(n));
    return 0;
}