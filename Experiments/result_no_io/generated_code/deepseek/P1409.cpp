#include <stdio.h>
#include <stdlib.h>

double calculate_probability(int n, int m) {
    double dp[1001][1001] = {0};
    dp[1][1] = 1.0;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i-1][j-1] * (1.0 / 6.0) + dp[i-1][j] * (3.0 / 6.0) + dp[i-1][j+1] * (2.0 / 6.0);
        }
    }

    return dp[n][m];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double probability = calculate_probability(n, m);
    printf("%.9f\n", probability);

    return 0;
}