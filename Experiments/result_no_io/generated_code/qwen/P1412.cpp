#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, k, c, w;
double dp[MAX_N][2];

int main() {
    scanf("%d %d %d %d", &n, &k, &c, &w);
    
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = -1e9;
        dp[i][1] = -1e9;
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; ++i) {
        int type, x;
        scanf("%d %d", &type, &x);

        if (type == 1) {
            double new_w = w * (1 - 0.01 * k);
            dp[i + 1][0] = fmax(dp[i + 1][0], dp[i][0] + x * w);
            dp[i + 1][1] = fmax(dp[i + 1][1], dp[i][1] + x * new_w);
        } else {
            double new_w = w * (1 + 0.01 * c);
            dp[i + 1][0] = fmax(dp[i + 1][0], dp[i][0] - x * w);
            dp[i + 1][1] = fmax(dp[i + 1][1], dp[i][1] - x * new_w);
        }

        dp[i + 1][0] = fmax(dp[i + 1][0], dp[i][0]);
        dp[i + 1][1] = fmax(dp[i + 1][1], dp[i][1]);
    }

    printf("%.2f\n", fmax(dp[n][0], dp[n][1]));
    return 0;
}