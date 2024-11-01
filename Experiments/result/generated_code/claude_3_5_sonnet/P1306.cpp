#include <stdio.h>

#define MOD 100000000

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void fibonacci(long long n, long long *fn, long long *fn1) {
    if (n == 0) {
        *fn = 0;
        *fn1 = 1;
        return;
    }
    long long a = 0, b = 1;
    for (long long i = 2; i <= n; i++) {
        long long c = (a + b) % MOD;
        a = b;
        b = c;
    }
    *fn = b;
    *fn1 = a;
}

long long fib_gcd(long long n, long long m) {
    long long fn, fn1, fm, fm1;
    fibonacci(n, &fn, &fn1);
    fibonacci(m, &fm, &fm1);
    return gcd(fn, fm);
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    long long result = fib_gcd(n, m);
    printf("%lld\n", result);
    return 0;
}