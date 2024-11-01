#include <stdio.h>
#include <stdlib.h>

#define MAX_P 100005
#define MAX_Q 1000000000
#define MAX_TEST 50

typedef struct {
    int prime;
    long long exponent;
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

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long find_x(long long N, int x) {
    long long result = N;
    for (int i = 1; i <= x; i++) {
        result = phi(result);
    }
    return result;
}

int main() {
    int test;
    scanf("%d", &test);
    while (test--) {
        int m;
        scanf("%d", &m);
        Factor factors[MAX_M];
        for (int i = 0; i < m; i++) {
            scanf("%d %lld", &factors[i].prime, &factors[i].exponent);
        }
        long long N = 1;
        for (int i = 0; i < m; i++) {
            N *= power(factors[i].prime, factors[i].exponent, 1LL << 63);
        }
        int x;
        scanf("%d", &x);
        printf("%lld\n", find_x(N, x));
    }
    return 0;
}