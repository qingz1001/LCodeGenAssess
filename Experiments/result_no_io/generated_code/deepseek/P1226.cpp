#include <stdio.h>

long long fast_pow(long long a, long long b, long long p) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    long long a, b, p;
    scanf("%lld %lld %lld", &a, &b, &p);
    long long s = fast_pow(a, b, p);
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, s);
    return 0;
}