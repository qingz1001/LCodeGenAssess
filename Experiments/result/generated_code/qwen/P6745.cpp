#include <stdio.h>

int main() {
    long long k, x;
    scanf("%lld %lld", &k, &x);
    printf("%lld\n", (long long)1e9 + x);
    return 0;
}