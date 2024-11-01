#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

long long power(long long base, int exp) {
    if (exp == 0) return 1;
    long long half_power = power(base, exp / 2);
    if (exp % 2 == 0) return (half_power * half_power) % MOD;
    else return ((base * half_power) * half_power) % MOD;
}

long long combination(int n, int k) {
    if (k > n) return 0;
    return (factorial(n) * power(factorial(k), MOD - 2) % MOD * power(factorial(n - k), MOD - 2)) % MOD;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *C = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        scanf("%d", &C[i]);
    }

    long long ways = 1;
    for (int i = 0; i < M; i++) {
        if (N - C[i] >= 0) {
            ways = (ways * combination(N - C[i], i + 1)) % MOD;
        } else {
            break;
        }
    }

    printf("%lld\n", ways);

    free(C);
    return 0;
}