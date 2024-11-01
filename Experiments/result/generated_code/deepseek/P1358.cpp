#include <stdio.h>

#define MOD 10007

int factorial[10001];
int inv_factorial[10001];

int mod_pow(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

void precompute_factorials(int n) {
    factorial[0] = 1;
    inv_factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
        inv_factorial[i] = mod_pow(factorial[i], MOD - 2);
    }
}

int combination(int n, int k) {
    if (k > n) return 0;
    return (factorial[n] * ((inv_factorial[k] * inv_factorial[n - k]) % MOD)) % MOD;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    precompute_factorials(n);

    int result = factorial[n];
    for (int i = 0; i < m; i++) {
        result = (result * inv_factorial[a[i]]) % MOD;
    }

    printf("%d\n", result);
    return 0;
}