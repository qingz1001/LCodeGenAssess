#include <stdio.h>

int main() {
    int a1, a2, n;
    scanf("%d %d %d", &a1, &a2, &n);
    
    int d = a2 - a1;
    long long sum = (long long)n * (2 * a1 + (n - 1) * d) / 2;
    
    printf("%lld\n", sum);
    
    return 0;
}