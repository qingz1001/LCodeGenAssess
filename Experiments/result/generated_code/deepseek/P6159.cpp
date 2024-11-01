#include <stdio.h>

int main() {
    long long n, p, k;
    scanf("%lld %lld %lld", &n, &p, &k);
    
    // Calculate the final position after k reflections
    long long t = (p * k) % n;
    
    printf("%lld\n", t);
    return 0;
}