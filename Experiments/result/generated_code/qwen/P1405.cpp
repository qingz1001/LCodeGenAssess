#include <stdio.h>

#define MOD 10007

int power(int base, int exp) {
    if (exp == 0) return 1;
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
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int result = 1;
    for (int i = n - 1; i >= 0; i--) {
        result = power(result, a[i]);
    }

    printf("%d\n", result);
    return 0;
}