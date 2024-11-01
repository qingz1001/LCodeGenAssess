#include <stdio.h>

long long countWays(long long n) {
    if (n == 1) return 8;
    long long m = 1;
    while (n > 0) {
        n -= m;
        m *= 2;
    }
    return m / 2;
}

int main() {
    long long n;
    scanf("%lld", &n);
    long long result = countWays(n);
    printf("%lld\n", result);
    return 0;
}