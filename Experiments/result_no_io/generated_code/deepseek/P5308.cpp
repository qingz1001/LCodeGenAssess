#include <stdio.h>
#include <math.h>

double dp[100001][101];

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        dp[i][1] = (double)i;
    }

    for (int j = 2; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            for (int x = 1; x <= i; x++) {
                dp[i][j] = max(dp[i][j], dp[x][j-1] + (double)(i - x) / i);
            }
        }
    }

    printf("%.9f\n", dp[n][k]);
    return 0;
}