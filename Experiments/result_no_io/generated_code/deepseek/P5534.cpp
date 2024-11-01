#include <stdio.h>

int main() {
    long long a1, a2, n;
    scanf("%lld %lld %lld", &a1, &a2, &n);
    
    long long d = a2 - a1;
    long long sum = n * a1 + n * (n - 1) / 2 * d;
    
    printf("%lld\n", sum);
    return 0;
}