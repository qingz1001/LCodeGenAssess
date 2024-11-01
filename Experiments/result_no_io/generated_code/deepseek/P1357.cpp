#include <stdio.h>
#include <stdint.h>

#define MOD 1000000007

int64_t mod_exp(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int64_t n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    if (k == 0) {
        printf("0\n");
        return 0;
    }

    int64_t result = mod_exp(k + 1, n, MOD);
    printf("%lld\n", result);

    return 0;
}