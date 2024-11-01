#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

long long quick_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

long long inv(long long x) {
    return quick_pow(x, MOD - 2);
}

long long C(long long n, long long k) {
    if (k > n) return 0;
    long long res = 1;
    for (long long i = 1; i <= k; i++) {
        res = res * (n - i + 1) % MOD * inv(i) % MOD;
    }
    return res;
}

int main() {
    long long N, M, S, L;
    scanf("%lld %lld %lld %lld", &N, &M, &S, &L);

    for (int i = 0; i < S; i++) {
        long long n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);

        long long result = 0;
        for (long long j = 0; j <= k; j++) {
            long long prob = C(m, j) * C(n - m, k - j) % MOD * inv(C(n, k)) % MOD;
            result = (result + quick_pow(j, L) * prob) % MOD;
        }

        printf("%lld\n", result);
    }

    return 0;
}