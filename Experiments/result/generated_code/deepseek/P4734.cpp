#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int values[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    int dp[MAXN][2];
    for (int i = 0; i < n; i++) {
        dp[i][0] = dp[i][1] = INT_MIN;
    }

    dp[0][0] = values[0];
    dp[1][1] = values[1];

    for (int i = 2; i < n; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-2][0] + values[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-2][1] + values[i]);
    }

    int result = max(dp[n-1][0], dp[n-2][1]);
    printf("%d\n", result);

    return 0;
}