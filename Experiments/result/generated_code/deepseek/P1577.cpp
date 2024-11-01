#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_L 100000.00

int compare(const void *a, const void *b) {
    return (*(double *)a > *(double *)b) ? -1 : 1;
}

int can_cut(double *lengths, int n, int k, double length) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += (int)(lengths[i] / length);
        if (count >= k) return 1;
    }
    return 0;
}

int main() {
    int N, K;
    double lengths[MAX_N];
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%lf", &lengths[i]);
    }

    qsort(lengths, N, sizeof(double), compare);

    double left = 0.01, right = lengths[0];
    double result = 0.00;

    while (right - left >= 0.01) {
        double mid = (left + right) / 2.0;
        if (can_cut(lengths, N, K, mid)) {
            result = mid;
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.2f\n", result);
    return 0;
}