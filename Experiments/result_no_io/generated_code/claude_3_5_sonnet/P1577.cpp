#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define EPS 1e-5

double L[MAX_N];
int N, K;

int check(double x) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        count += (int)(L[i] / x);
    }
    return count >= K;
}

double solve() {
    double left = 0, right = 100000;
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
        scanf("%lf", &L[i]);
    }
    
    double result = solve();
    printf("%.2f\n", (int)(result * 100) / 100.0);
    
    return 0;
}