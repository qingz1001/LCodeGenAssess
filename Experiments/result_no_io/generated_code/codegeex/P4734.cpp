#include <stdio.h>
#include <string.h>

int n, a[2005], dp[2005][2005], f[2005][2005], g[2005][2005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j] + a[i];
            f[i][j] = f[i][j - 1] + a[i];
            g[i][j] = g[i - 1][j - 1] + a[i];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int p = dp[i - 1][j - 1] + dp[j + 1][n] - dp[j][j];
            int q = f[i - 1][j - 1] + f[j + 1][n] - f[j][j];
            int r = g[i - 1][j - 1] + g[j + 1][n] - g[j][j];
            ans = (ans > p + q - r) ? ans : p + q - r;
        }
    }

    printf("%d\n", ans);
    return 0;
}