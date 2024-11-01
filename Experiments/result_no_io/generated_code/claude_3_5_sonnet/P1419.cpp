#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, S, T;
    int a[MAX_N + 1];
    double sum[MAX_N + 1] = {0};
    double maxAvg = -1e9;

    scanf("%d", &n);
    scanf("%d %d", &S, &T);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = sum[i-1] + a[i];
    }

    for (int len = S; len <= T; len++) {
        for (int i = len; i <= n; i++) {
            double avg = (sum[i] - sum[i-len]) / len;
            maxAvg = max(maxAvg, avg);
        }
    }

    printf("%.3f\n", maxAvg);

    return 0;
}