#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define EPS 1e-9

int N;
long long M[MAX_N + 1];
long long sum[MAX_N + 1];

int check(double x) {
    double min_prefix = 0;
    double prefix = 0;
    for (int i = 1; i < N; i++) {
        prefix += M[i] - x;
        if (i >= 2) {
            if (prefix - min_prefix >= -EPS) return 1;
            if (prefix < min_prefix) min_prefix = prefix;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &M[i]);
        sum[i] = sum[i-1] + M[i];
    }

    double left = 0, right = 10000;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    printf("%.3f\n", left);
    return 0;
}