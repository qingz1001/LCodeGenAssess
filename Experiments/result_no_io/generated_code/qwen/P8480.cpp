#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long *a = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    // Find the maximum and minimum values in the array
    long long max_val = a[0];
    long long min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
        if (a[i] < min_val) {
            min_val = a[i];
        }
    }

    // The maximum possible difference after m operations is achieved by maximizing the largest value or minimizing the smallest value
    // Since we can double or halve any number, the largest value can be at most max_val + 2*m and the smallest value can be at least min_val - 2*m
    long long result = max_val + 2 * m - (min_val - 2 * m);

    printf("%lld\n", result);

    free(a);
    return 0;
}