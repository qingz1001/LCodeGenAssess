#include <stdio.h>
#include <stdlib.h>

#define MAX_P 100005
#define MAX_Q 1000000000
#define MAX_TEST 50

typedef struct {
    int prime;
    int exponent;
} Factor;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long phi(long long n) {
    long long result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int find_min_x(long long N, int x) {
    for (int i = 1; i <= x; i++) {
        N = phi(N);
    }
    return N == 1 ? i : -1;
}

int main() {
    int test;
    scanf("%d", &test);

    for (int t = 0; t < test; t++) {
        int m;
        scanf("%d", &m);
        long long N = 1;
        Factor factors[MAX_M];
        int factor_count = 0;

        for (int i = 0; i < m; i++) {
            int p, q;
            scanf("%d %d", &p, &q);
            factors[factor_count].prime = p;
            factors[factor_count].exponent = q;
            factor_count++;
            N *= (long long)p * p;
        }

        int x;
        scanf("%d", &x);

        int result = find_min_x(N, x);
        printf("%d\n", result);
    }

    return 0;
}