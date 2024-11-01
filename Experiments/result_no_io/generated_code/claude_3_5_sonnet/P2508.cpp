#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    long long r;
    scanf("%lld", &r);
    
    long long count = 0;
    
    for (long long x = 1; x <= r; x++) {
        long long y = r * r - x * x;
        long long sqrty = (long long)sqrt(y);
        if (sqrty * sqrty == y) {
            count += 4;
        }
    }
    
    printf("%lld\n", count + 4);
    
    return 0;
}