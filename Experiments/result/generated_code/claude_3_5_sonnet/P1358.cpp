#include <stdio.h>

#define MOD 10007

long long factorial[10001];

void init_factorial() {
    factorial[0] = 1;
    for (int i = 1; i <= 10000; i++) {
        factorial[i] = (factorial[i-1] * i) % MOD;
    }
}

long long pow_mod(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

long long inverse(long long x) {
    return pow_mod(x, MOD - 2);
}

int main() {
    init_factorial();

    int n, m;
    scanf("%d %d", &n, &m);

    long long result = factorial[n];
    for (int i = 0; i < m; i++) {
        int ai;
        scanf("%d", &ai);
        result = (result * inverse(factorial[ai])) % MOD;
    }

    printf("%lld\n", result);

    return 0;
}