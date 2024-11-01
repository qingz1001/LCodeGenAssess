#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, S, T;
    scanf("%d", &n);
    scanf("%d %d", &S, &T);

    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    double max_avg = INT_MIN;

    for (int len = S; len <= T; len++) {
        double sum = 0;
        for (int i = 0; i < len; i++) {
            sum += a[i];
        }
        max_avg = max(max_avg, sum / len);

        for (int i = len; i < n; i++) {
            sum += a[i] - a[i - len];
            max_avg = max(max_avg, sum / len);
        }
    }

    printf("%.3f\n", max_avg);

    free(a);
    return 0;
}