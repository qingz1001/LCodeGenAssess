#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int h, t, n;
    scanf("%d%d%d", &h, &t, &n);

    int dp[h + 1][t + 1];
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int hi, ti, ki;
        scanf("%d%d%d", &hi, &ti, &ki);
        for (int j = h; j >= hi; j--) {
            for (int k = t; k >= ti; k--) {
                dp[j][k] = max(dp[j][k], dp[j - hi][k - ti] + ki);
            }
        }
    }

    printf("%d\n", dp[h][t]);
    return 0;
}