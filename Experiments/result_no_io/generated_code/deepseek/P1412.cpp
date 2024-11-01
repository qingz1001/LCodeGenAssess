#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

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

    Planet planets[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &planets[i].type, &planets[i].value);
    }

    double dp[MAXN + 1];
    dp[n] = 0.0;

    for (int i = n - 1; i >= 0; i--) {
        if (planets[i].type == 1) {
            dp[i] = max(dp[i + 1], dp[i + 1] + planets[i].value * w * (1 - 0.01 * k));
        } else {
            dp[i] = max(dp[i + 1], dp[i + 1] - planets[i].value * w * (1 + 0.01 * c));
        }
    }

    printf("%.2f\n", dp[0]);

    return 0;
}