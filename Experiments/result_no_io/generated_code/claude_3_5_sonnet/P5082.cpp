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

    long long sum_deducted = sum_full - sum_actual;
    double comprehensive_score = (sum_full * 3.0 - sum_actual * 2.0) / sum_deducted;

    printf("%.6f\n", comprehensive_score);

    return 0;
}