#include <stdio.h>

#define MOD 10007

int quick_pow(int base, int exp) {
    int result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    int n, a;
    scanf("%d", &n);
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        if (i == n - 1) {
            result = a % MOD;
        } else {
            result = quick_pow(a, result ? result : MOD - 1);
        }
    }
    
    printf("%d\n", result);
    return 0;
}