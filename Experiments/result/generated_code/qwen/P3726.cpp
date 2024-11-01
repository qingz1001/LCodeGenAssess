#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long power(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b, k;
        scanf("%lld %lld %lld", &a, &b, &k);

        long long total_ways = power(2, a + b);
        long long ways_A_more_heads = 0;

        for (long long i = b; i <= a; ++i) {
            long long binom = 1;
            for (long long j = 1; j <= i; ++j) {
                binom = (binom * (a - b + i)) % MOD;
                binom = (binom * power(j, MOD - 2)) % MOD;
            }
            ways_A_more_heads = (ways_A_more_heads + binom) % MOD;
        }

        printf("%0*lld\n", k, ways_A_more_heads);
    }
    return 0;
}