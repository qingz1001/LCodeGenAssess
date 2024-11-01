#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000
#define MAX_DP 101

typedef struct {
    int type;
    int value;
} Planet;

Planet planets[MAX_N];
double dp[MAX_N][MAX_DP];

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, k, c, w;
    scanf("%d %d %d %d", &n, &k, &c, &w);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &planets[i].type, &planets[i].value);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 100; j++) {
            dp[i][j] = -1e9;
        }
    }

    dp[0][w] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 100; j++) {
            if (dp[i][j] < -1e8) continue;

            if (planets[i].type == 1) {
                // Resource planet
                int new_j = (int)(j * (100 - k) / 100.0);
                dp[i+1][new_j] = max(dp[i+1][new_j], dp[i][j] + j * planets[i].value);
                dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            } else {
                // Repair planet
                int new_j = fmin(100, (int)(j * (100 + c) / 100.0));
                dp[i+1][new_j] = max(dp[i+1][new_j], dp[i][j] - j * planets[i].value);
                dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            }
        }
    }

    double max_profit = -1e9;
    for (int j = 1; j <= 100; j++) {
        max_profit = max(max_profit, dp[n][j]);
    }

    printf("%.2f\n", max_profit);

    return 0;
}