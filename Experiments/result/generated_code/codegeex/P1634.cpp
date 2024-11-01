#include <stdio.h>

int main() {
    unsigned long long x, n, result = 0;
    scanf("%llu %llu", &x, &n);

    for (unsigned long long i = 0; i < n; i++) {
        result += x;
        x *= 10;
    }

    printf("%llu\n", result);
    return 0;
}