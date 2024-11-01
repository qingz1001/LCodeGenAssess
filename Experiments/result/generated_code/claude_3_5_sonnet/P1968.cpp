#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 100

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int N;
    double rates[MAX_DAYS + 1];
    double dp[MAX_DAYS + 1][2];  // dp[i][0]: 美元, dp[i][1]: 马克

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lf", &rates[i]);
    }

    dp[0][0] = 100.0;
    dp[0][1] = 0.0;

    for (int i = 1; i <= N; i++) {
        // 保持美元
        dp[i][0] = dp[i-1][0];
        // 美元换马克
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] * rates[i] / 100.0);

        // 保持马克
        dp[i][1] = max(dp[i][1], dp[i-1][1]);
        // 马克换美元
        dp[i][0] = max(dp[i][0], dp[i-1][1] * 100.0 / rates[i]);
    }

    printf("%.2f\n", dp[N][0]);

    return 0;
}