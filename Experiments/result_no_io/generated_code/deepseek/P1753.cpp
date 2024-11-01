#include <stdio.h>
#include <limits.h>

#define MAXN 2000001
#define MAXW 10001

int dp[MAXN][MAXN];
int w[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + w[i-1] * w[k] * w[j]);
            }
        }
    }

    printf("%d\n", dp[1][n]);
    return 0;
}