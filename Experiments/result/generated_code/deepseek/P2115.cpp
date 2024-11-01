#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 100000

int machines[MAXN];
int N;

double calculate_min_avg(int *machines, int N) {
    double left = 1.0, right = 10000.0;
    double eps = 1e-6;

    while (right - left > eps) {
        double mid = (left + right) / 2.0;
        double prefix_sum = 0.0;
        double min_prefix_sum = 0.0;
        double total_sum = 0.0;
        int i;

        for (i = 0; i < N; i++) {
            total_sum += machines[i] - mid;
        }

        int valid = 0;
        for (i = 1; i < N - 1; i++) {
            prefix_sum += machines[i - 1] - mid;
            if (prefix_sum < min_prefix_sum) {
                min_prefix_sum = prefix_sum;
            }
            if (total_sum - prefix_sum - (machines[i] - mid) > min_prefix_sum) {
                valid = 1;
                break;
            }
        }

        if (valid) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

int main() {
    scanf("%d", &N);
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &machines[i]);
    }

    double result = calculate_min_avg(machines, N);
    printf("%.3f\n", result);

    return 0;
}