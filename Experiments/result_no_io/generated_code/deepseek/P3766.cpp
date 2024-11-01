#include <stdio.h>
#include <math.h>

#define MAX_N 1000000

double g[MAX_N + 1];

void precompute_g() {
    for (int i = 2; i <= MAX_N; i++) {
        g[i] = 0;
        for (int k = 2; k <= 64; k++) { // 64 is an arbitrary upper limit for k
            long long root = (long long)round(pow(i, 1.0 / k));
            if (root > 1 && pow(root, k) == i) {
                g[i]++;
            }
        }
    }
}

double compute_f(int n) {
    double result = 0.0;
    for (int i = 2; i <= n; i++) {
        result += g[i] / i;
    }
    return result;
}

int main() {
    precompute_g();

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%.14f\n", compute_f(n));
    }

    return 0;
}