#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long fibonacci(long long n) {
    long long a = 0, b = 1, c;
    if (n == 0) return a;
    for (long long i = 2; i <= n; i++) {
        c = (a + b) % 100000000;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    long long fn = fibonacci(n);
    long long fm = fibonacci(m);
    long long result = gcd(fn, fm);
    printf("%lld\n", result);
    return 0;
}