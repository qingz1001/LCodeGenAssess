#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

int catalan_number(int n) {
    if (n == 0 || n == 1) return 1;
    int C[n + 1];
    C[0] = C[1] = 1;
    for (int i = 2; i <= n; i++) {
        C[i] = 0;
        for (int j = 0; j < i; j++) {
            C[i] = (C[i] + ((long long)C[j] * C[i - j - 1]) % MOD) % MOD;
        }
    }
    return C[n];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int result = 0;
    for (int i = 0; i <= n; i++) {
        result = (result + ((long long)catalan_number(i) * factorial(n)) % MOD) % MOD;
    }
    printf("%d\n", result);
    return 0;
}