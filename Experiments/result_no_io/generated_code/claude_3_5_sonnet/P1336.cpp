#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 201
#define MAX_M 21
#define INF 1e18

double dp[MAX_N];
int A[MAX_M], B[MAX_M];

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 1; k <= i; k++) {
                dp[i] = min(dp[i], dp[i-k] + A[j] * pow(k, B[j]));
            }
        }
    }

    printf("%.0f\n", dp[n]);

    return 0;
}