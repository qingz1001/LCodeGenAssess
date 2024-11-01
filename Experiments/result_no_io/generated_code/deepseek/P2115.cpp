#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 100000

int N;
int M[MAXN];
double sum[MAXN];

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

int check(double avg) {
    sum[0] = 0;
    for (int i = 1; i <= N; i++) {
        sum[i] = sum[i - 1] + (M[i - 1] - avg);
    }

    double min_prefix = 0;
    for (int i = 2; i < N; i++) {
        if (sum[i] - min_prefix < 0) {
            return 1;
        }
        min_prefix = min(min_prefix, sum[i - 1]);
    }
    return 0;
}

double binary_search(double left, double right) {
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (left + right) / 2;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &M[i]);
    }

    double left = 0, right = 10000;
    double result = binary_search(left, right);

    printf("%.3f\n", result);

    return 0;
}