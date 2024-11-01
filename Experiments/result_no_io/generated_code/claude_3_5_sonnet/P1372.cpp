#include <stdio.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);

    if (k == 1) {
        printf("%lld\n", n);
        return 0;
    }

    long long result = n / k;
    
    printf("%lld\n", result);
    return 0;
}