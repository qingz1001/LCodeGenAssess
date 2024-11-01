#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_L 100000.00

int compare(const void *a, const void *b) {
    return (*(double *)a > *(double *)b) ? -1 : 1;
}

int can_cut(double *lengths, int n, int k, double len) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += (int)(lengths[i] / len);
        if (count >= k) return 1;
    }
    return 0;
}

double max_length(double *lengths, int n, int k) {
    qsort(lengths, n, sizeof(double), compare);
    double left = 0.0, right = lengths[0];
    while (right - left > 0.001) {
        double mid = (left + right) / 2.0;
        if (can_cut(lengths, n, k, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    int n, k;
    double lengths[MAX_N];

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &lengths[i]);
    }

    double result = max_length(lengths, n, k);
    printf("%.2f\n", result);

    return 0;
}