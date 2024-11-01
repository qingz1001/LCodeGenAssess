#include <stdio.h>

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    long long n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);

    long long g = gcd(n, p);
    long long m = n / g;
    
    long long t = (p * k) % n;
    
    if (k >= m) {
        k %= m;
        t = (p * k) % n;
    }
    
    printf("%lld\n", t);
    
    return 0;
}