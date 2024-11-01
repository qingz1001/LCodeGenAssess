#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define EPS 1e-5

double lengths[MAX_N];
int N, K;

int check(double x) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += (int)(lengths[i] / x);
    }
    return count >= K;
}

double binary_search() {
    double left = 0, right = 100000.0;
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%lf", &lengths[i]);
    }

    double result = binary_search();
    printf("%.2f\n", (int)(result * 100) / 100.0);

    return 0;
}