#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int a[100005][3];
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    }

    int dp[100005][3];
    dp[0][0] = a[0][0];
    dp[0][1] = a[0][1];
    dp[0][2] = a[0][2];

    for (int i = 1; i < n; i++) {
        dp[i][0] = a[i][0] + (dp[i-1][1] > dp[i-1][2] ? dp[i-1][1] : dp[i-1][2]);
        dp[i][1] = a[i][1] + (dp[i-1][0] > dp[i-1][2] ? dp[i-1][0] : dp[i-1][2]);
        dp[i][2] = a[i][2] + (dp[i-1][0] > dp[i-1][1] ? dp[i-1][0] : dp[i-1][1]);
    }

    int result = dp[n-1][0];
    for (int i = 1; i < 3; i++) {
        if (dp[n-1][i] > result) {
            result = dp[n-1][i];
        }
    }

    printf("%d\n", result);

    return 0;
}