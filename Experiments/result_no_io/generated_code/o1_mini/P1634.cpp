#include <stdio.h>
#include <stdint.h>

typedef unsigned long long ull;

int main() {
    ull x, n;
    scanf("%llu %llu", &x, &n);
    ull result;
    if (x == 1) {
        result = n + 1;
    } else {
        ull power = 1;
        ull exponent = n + 1;
        ull base = x;
        while (exponent > 0) {
            if (exponent & 1)
                power *= base;
            base *= base;
            exponent >>= 1;
        }
        result = (power - 1) / (x - 1);
    }
    printf("%llu\n", result);
    return 0;
}