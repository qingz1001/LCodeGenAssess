#include <stdio.h>

#define MAXN 19

int dp[MAXN][MAXN];

void calculate(int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    calculate(n);
    printf("%d\n", dp[n][n]);
    return 0;
}