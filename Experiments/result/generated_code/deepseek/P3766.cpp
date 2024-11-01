#include <stdio.h>
#include <math.h>

#define MAX_N 1000000
#define EPSILON 2e-14

int g[MAX_N + 1];
double f[MAX_N + 1];

void preprocess() {
    for (int i = 2; i <= MAX_N; i++) {
        g[i] = 0;
        for (int k = 2; k <= (int)log2(i); k++) {
            int base = (int)round(pow(i, 1.0 / k));
            if (pow(base, k) == i) {
                g[i]++;
            }
        }
    }

    f[2] = (double)g[2] / 2;
    for (int i = 3; i <= MAX_N; i++) {
        f[i] = f[i - 1] + (double)g[i] / i;
    }
}

int main() {
    preprocess();

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n > MAX_N) {
            printf("%.14f\n", f[MAX_N]);
        } else {
            printf("%.14f\n", f[n]);
        }
    }

    return 0;
}