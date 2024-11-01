#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char lights[n + 1];
    scanf("%s", lights);

    int dp[n + 1][k + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (lights[i - 1] == 'N') {
            dp[i][0] = dp[i - 1][0] + 1;
        } else {
            dp[i][0] = 1;
        }
    }

    for (int j = 1; j <= k; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (lights[i - 1] == 'N') {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]);
            }
        }
    }

    int result = n;
    for (int j = 0; j <= k; j++) {
        result = min(result, dp[n][j]);
    }

    printf("%d\n", result);

    return 0;
}