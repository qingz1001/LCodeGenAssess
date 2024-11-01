#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 8000
#define MAXK 1000000000
#define MAXP 3000

int n, k, p;
double h[MAXN + 1];

double max(double a, double b) {
    return a > b ? a : b;
}

double solve() {
    double dp[MAXN + 1][MAXK + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0.0;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = h[1];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int m = 1; m < i; m++) {
                double avg = 0.0;
                for (int l = m; l <= i; l++) {
                    avg += h[l];
                }
                avg /= (i - m + 1);
                dp[i][j] = max(dp[i][j], max(dp[m - 1][j - 1], avg));
            }
        }
    }

    return dp[n][k];
}

int main() {
    scanf("%d %d %d", &n, &k, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &h[i]);
    }

    double result = solve();
    printf("%.20lf\n", result);

    return 0;
}