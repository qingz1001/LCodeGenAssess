#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int power(int base, int exp, int mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return (int)result;
}

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    long long total = 0;
    for (int i = 0; i <= m; ++i) {
        long long comb = 1;
        for (int j = 0; j < i; ++j) {
            comb = comb * (n - j) / (j + 1);
        }
        total = (total + comb) % MOD;
    }

    printf("%lld\n", power(total, p - 2, MOD));
    return 0;
}