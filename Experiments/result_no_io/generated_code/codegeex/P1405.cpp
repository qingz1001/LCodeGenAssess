#include <stdio.h>

#define MOD 10007

int power(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent /= 2;
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
    int result = a[0];
    for (int i = 1; i < n; i++) {
        result = power(result, a[i]);
    }
    printf("%d\n", result);
    return 0;
}