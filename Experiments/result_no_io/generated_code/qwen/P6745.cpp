#include <stdio.h>

int main() {
    long long k, x;
    scanf("%lld %lld", &k, &x);
    printf("%lld\n", (long long)1e9 * (1LL << k) + x);
    return 0;
}