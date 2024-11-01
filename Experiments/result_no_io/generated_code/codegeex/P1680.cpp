#include <stdio.h>

#define MOD 1000000007

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

long long combination(int n, int k) {
    if (k > n) return 0;
    long long numerator = factorial(n);
    long long denominator = (factorial(k) * factorial(n - k)) % MOD;
    return (numerator * pow(denominator, MOD - 2, MOD)) % MOD;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int C[1000000];
    for (int i = 0; i < M; i++) {
        scanf("%d", &C[i]);
    }

    long long result = 1;
    for (int i = 0; i < M; i++) {
        result = (result * combination(N - C[i], M - i)) % MOD;
    }

    printf("%lld\n", result);
    return 0;
}