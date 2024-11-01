#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int type;
    int value;
} Planet;

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, k, c, w;
    scanf("%d %d %d %d", &n, &k, &c, &w);

    Planet planets[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &planets[i].type, &planets[i].value);
    }

    double dp[MAX_N + 1][2] = {0};
    
    for (int i = n - 1; i >= 0; i--) {
        if (planets[i].type == 1) {  // Resource planet
            double mine = planets[i].value * w * (1 - 0.01 * k * i) + dp[i + 1][0];
            double skip = dp[i + 1][0];
            dp[i][0] = max(mine, skip);
            dp[i][1] = dp[i + 1][1];
        } else {  // Repair planet
            double repair = -planets[i].value * w * (1 + 0.01 * c * i) + dp[i + 1][1];
            double skip = dp[i + 1][0];
            dp[i][0] = dp[i + 1][0];
            dp[i][1] = max(repair, skip);
        }
    }

    printf("%.2f\n", max(dp[0][0], dp[0][1]));

    return 0;
}