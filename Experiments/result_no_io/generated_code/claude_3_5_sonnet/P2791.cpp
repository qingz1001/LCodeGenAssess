#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

long long fast_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

long long inverse(long long x) {
    return fast_pow(x, MOD - 2);
}

long long C(long long n, long long k) {
    if (k > n) return 0;
    long long res = 1;
    for (long long i = 1; i <= k; i++) {
        res = (res * (n - i + 1)) % MOD;
        res = (res * inverse(i)) % MOD;
    }
    return res;
}

int main() {
    int N, M, S, L;
    scanf("%d %d %d %d", &N, &M, &S, &L);

    for (int i = 0; i < S; i++) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        long long exp = 0;
        for (int j = 0; j <= k; j++) {
            long long prob = (C(m, j) * C(n - m, k - j)) % MOD;
            prob = (prob * inverse(C(n, k))) % MOD;
            exp = (exp + (fast_pow(j, L) * prob) % MOD) % MOD;
        }

        printf("%lld\n", exp);
    }

    return 0;
}