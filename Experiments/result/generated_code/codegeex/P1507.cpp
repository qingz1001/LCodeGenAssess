#include <stdio.h>

int main() {
    int h, t, n;
    scanf("%d %d", &h, &t);
    scanf("%d", &n);

    int v[55], w[55], c[55];
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &v[i], &w[i], &c[i]);
    }

    int dp[405][405];
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = h; j >= v[i]; j--) {
            for (int k = t; k >= w[i]; k--) {
                dp[j][k] = (dp[j][k] > dp[j - v[i]][k - w[i]] + c[i]) ? dp[j][k] : dp[j - v[i]][k - w[i]] + c[i];
            }
        }
    }

    printf("%d\n", dp[h][t]);
    return 0;
}