#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000000000000000LL

long long k(long long n) {
    if (n == 1) return 1;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0 && k(n / i) != -1) {
            return i;
        }
    }
    return -1;
}

int main() {
    long long n, count = 0;
    scanf("%lld", &n);
    long long kn = k(n);
    printf("%lld ", kn == -1 ? -1 : kn);
    for (long long i = 1; i <= n; i++) {
        if (k(i) < k(i + 1)) {
            count++;
        }
    }
    printf("%lld\n", count);
    return 0;
}