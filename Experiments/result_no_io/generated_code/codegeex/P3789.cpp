#include <stdio.h>
#include <stdint.h>

#define MOD 998244353

typedef __int128 int128_t;

int128_t fast_pow(int128_t base, int128_t exp, int128_t mod) {
    int128_t result = 1;
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
    int128_t n, k;
    scanf("%" PRId128 " %" PRId128, &n, &k);

    int128_t a = fast_pow(2, n, MOD);
    int128_t b = fast_pow(3, n, MOD);
    int128_t c = (a - b + MOD) % MOD;

    int128_t result = fast_pow(c, k, MOD);

    printf("%" PRId128, result);

    return 0;
}