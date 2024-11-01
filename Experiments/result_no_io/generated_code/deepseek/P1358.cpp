#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

// 计算组合数 C(n, k) % MOD
int comb(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k == 1 || k == n - 1) return n % MOD;

    int numerator = 1, denominator = 1;
    for (int i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }

    // 计算逆元
    int inv_denominator = 1;
    int base = denominator;
    int exp = MOD - 2;
    while (exp > 0) {
        if (exp % 2 == 1) {
            inv_denominator = (inv_denominator * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }

    return (numerator * inv_denominator) % MOD;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    int result = 1;
    int total_cards = 0;
    for (int i = 0; i < m; i++) {
        result = (result * comb(n - total_cards, a[i])) % MOD;
        total_cards += a[i];
    }

    printf("%d\n", result);
    free(a);
    return 0;
}