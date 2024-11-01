#include <stdio.h>

#define MOD 10007

int pow_mod(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n, i;
    scanf("%d", &n);

    int result = 0;
    int current;
    for (i = 0; i < n; i++) {
        scanf("%d", &current);
        if (i == n - 1) {
            result = current;
        } else {
            result = pow_mod(current, result, MOD - 1);
        }
    }

    printf("%d\n", pow_mod(result, 1, MOD));
    return 0;
}