#include <stdio.h>

#define MAXN 19

int dp[MAXN][MAXN];

void solve(int n) {
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= i) {
                dp[i][j] += dp[i - 1][j - i];
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    solve(n);
    printf("%d\n", dp[n][n]);
    return 0;
}