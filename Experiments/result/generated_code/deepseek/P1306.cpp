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

long long fib(long long n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (long long i = 2; i <= n; i++) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    long long g = gcd(n, m);
    long long result = fib(g);
    
    printf("%lld\n", result);
    
    return 0;
}