#include <stdio.h>
#include <math.h>

#define MAX_N 7
#define INF 1e9

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    double D[MAX_N], Price[MAX_N];
    D[0] = 0;
    Price[0] = P;
    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &D[i], &Price[i]);
    }
    D[N+1] = D1;
    Price[N+1] = INF;

    double dp[MAX_N];
    dp[0] = 0;

    for (int i = 1; i <= N + 1; i++) {
        dp[i] = INF;
        if (D[i] - D[i-1] > C * D2) {
            printf("No Solution\n");
            return 0;
        }
        for (int j = 0; j < i; j++) {
            if (D[i] - D[j] <= C * D2) {
                dp[i] = min(dp[i], dp[j] + (D[i] - D[j]) / D2 * Price[j]);
            }
        }
    }

    printf("%.2f\n", round(dp[N+1] * 100) / 100);
    return 0;
}