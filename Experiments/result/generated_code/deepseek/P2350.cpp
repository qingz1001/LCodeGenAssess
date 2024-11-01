#include <stdio.h>
#include <stdbool.h>

#define MAX_P 100005
#define MAX_TEST 50
#define MAX_M 2000

long long phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

long long min_x(int m, int p[], int q[]) {
    long long x = 0;
    bool has_even = false;
    for (int i = 0; i < m; ++i) {
        if (p[i] == 2) {
            has_even = true;
        }
        x += (p[i] - 1) * q[i];
    }
    if (!has_even) {
        x++;
    }
    return x;
}

int main() {
    int test;
    scanf("%d", &test);
    for (int t = 0; t < test; ++t) {
        int m;
        scanf("%d", &m);
        int p[MAX_M], q[MAX_M];
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &p[i], &q[i]);
        }
        printf("%lld\n", min_x(m, p, q));
    }
    return 0;
}