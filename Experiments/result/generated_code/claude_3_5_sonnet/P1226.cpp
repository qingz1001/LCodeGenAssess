#include <stdio.h>

long long quick_pow(long long a, long long b, long long p) {
    long long result = 1;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    return result;
}

int main() {
    long long a, b, p;
    scanf("%lld %lld %lld", &a, &b, &p);
    
    long long result = quick_pow(a, b, p);
    
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, result);
    
    return 0;
}