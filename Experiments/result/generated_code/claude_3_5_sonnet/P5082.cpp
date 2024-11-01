#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    long long sum_full = 0, sum_actual = 0;
    for (int i = 0; i < n; i++) {
        int full;
        scanf("%d", &full);
        sum_full += full;
    }

    for (int i = 0; i < n; i++) {
        int actual;
        scanf("%d", &actual);
        sum_actual += actual;
    }

    long long numerator = sum_full * 3 - sum_actual * 2;
    long long denominator = sum_full - sum_actual;

    double result = (double)numerator / denominator;
    printf("%.6f\n", result);

    return 0;
}