#include <stdio.h>

int main() {
    unsigned long long x, n;
    scanf("%llu %llu", &x, &n);
    unsigned long long result = (1ULL << n) - 1;
    printf("%llu\n", result * x);
    return 0;
}