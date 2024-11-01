#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 100

double max(double a, double b) {
    return (a > b) ? a : b;
}

int main() {
    int N, i;
    double rates[MAX_DAYS];
    double dp[MAX_DAYS][2]; // dp[i][0] for USD, dp[i][1] for DEM

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%lf", &rates[i]);
    }

    // Initialize
    dp[0][0] = 100.0;
    dp[0][1] = 100.0 * rates[0];

    // Dynamic Programming
    for (i = 1; i < N; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1] / rates[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] * rates[i]);
    }

    // Final result should be in USD
    printf("%.2f\n", dp[N-1][0]);

    return 0;
}