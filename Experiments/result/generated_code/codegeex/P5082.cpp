#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    long long sum_full = 0, sum_actual = 0, sum_deducted = 0;

    for (int i = 0; i < n; i++) {
        int full, actual;
        scanf("%d", &full);
        sum_full += full;
        scanf("%d", &actual);
        sum_actual += actual;
        sum_deducted += full - actual;
    }

    double result = (sum_full * 3.0 - sum_actual * 2.0) / sum_deducted;
    printf("%.6f\n", result);

    return 0;
}