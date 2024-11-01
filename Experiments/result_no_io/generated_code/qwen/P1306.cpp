#include <stdio.h>

#define MOD 100000000

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long fibonacci(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long fn = fibonacci(n);
    long long fm = fibonacci(m);
    printf("%lld\n", gcd(fn, fm));
    return 0;
}