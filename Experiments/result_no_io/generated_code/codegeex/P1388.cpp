#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[15];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int dp[15][15][15] = {0}; // dp[i][j][p] 表示从第 i 个数字到第 j 个数字，用 p 个乘号的最大值
    int min_dp[15][15][15] = {0}; // min_dp[i][j][p] 表示从第 i 个数字到第 j 个数字，用 p 个乘号的最小值

    for (int i = 0; i < n; i++) {
        dp[i][i][0] = a[i];
        min_dp[i][i][0] = a[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int p = 0; p <= min(k, j - i); p++) {
                if (p == 0) {
                    dp[i][j][p] = a[i] + min_dp[i + 1][j][0];
                } else {
                    dp[i][j][p] = max(dp[i][j][p], dp[i][j - 1][p - 1] * a[j]);
                    dp[i][j][p] = max(dp[i][j][p], dp[i][i][p] + min_dp[i + 1][j][0]);
                }
                min_dp[i][j][p] = min(min_dp[i][j][p], dp[i][j][p]);
            }
        }
    }

    printf("%d\n", dp[0][n - 1][k]);
    return 0;
}