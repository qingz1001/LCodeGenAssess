#include <stdio.h>
#include <limits.h>

#define MAXN 201

int main() {
    int n;
    scanf("%d", &n);

    int r[MAXN][MAXN];
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &r[i][j]);
        }
    }

    int dp[MAXN];
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    dp[1] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dp[i] != INT_MAX && dp[i] + r[i][j] < dp[j]) {
                dp[j] = dp[i] + r[i][j];
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}