#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long abs_val(long long x) {
    return x < 0 ? -x : x;
}

int main() {
    int n;
    scanf("%d", &n);
    long long *a = (long long *)malloc(n * sizeof(long long));
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }

    long long avg = sum / n;
    long long *c = (long long *)malloc(n * sizeof(long long));
    c[0] = 0;

    for (int i = 1; i < n; i++) {
        c[i] = c[i - 1] + a[i - 1] - avg;
    }

    qsort(c, n, sizeof(long long), (int (*)(const void *, const void *))strcmp);

    long long median = c[n / 2];
    long long cost = 0;

    for (int i = 0; i < n; i++) {
        cost += abs_val(c[i] - median);
    }

    printf("%lld\n", cost);

    free(a);
    free(c);

    return 0;
}