#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

long long power(long long base, int exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

long long binomial_coefficient(int n, int k) {
    if (k > n)
        return 0;
    long long numerator = 1, denominator = 1;
    for (int i = 1; i <= k; ++i) {
        numerator = (numerator * (n - i + 1)) % MOD;
        denominator = (denominator * i) % MOD;
    }
    return (numerator * power(denominator, MOD - 2)) % MOD;
}

int main() {
    int N, M, S, L;
    scanf("%d %d %d %d", &N, &M, &S, &L);
    
    for (int i = 0; i < S; ++i) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        
        long long total_ways = binomial_coefficient(n, k);
        long long successful_ways = binomial_coefficient(m, k);
        long long failed_ways = total_ways - successful_ways;
        
        long long expected_failure = (failed_ways * power(k, L)) % MOD;
        printf("%lld\n", expected_failure);
    }
    
    return 0;
}