#include <stdio.h>

long long mod(long long a, long long b) {
    return (a % b + b) % b;
}

int main() {
    long long n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);
    
    long long t = mod(p * (k + 1) - k, n);
    
    printf("%lld\n", t);
    
    return 0;
}