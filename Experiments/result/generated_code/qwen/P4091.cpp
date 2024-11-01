#include <stdio.h>

#define MOD 998244353

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result = (result * i) % MOD;
    }
    return result;
}

int stirling_second_kind(int n, int k) {
    if (n == k) return 1;
    if (k == 0) return 0;
    int result = ((long long)k * stirling_second_kind(n - 1, k)) % MOD;
    result = (result + stirling_second_kind(n - 1, k - 1)) % MOD;
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long f_n = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            long long term = (stirling_second_kind(i, j) * (1LL << j)) % MOD;
            term = (term * factorial(j)) % MOD;
            f_n = (f_n + term) % MOD;
        }
    }
    
    printf("%lld\n", f_n);
    return 0;
}