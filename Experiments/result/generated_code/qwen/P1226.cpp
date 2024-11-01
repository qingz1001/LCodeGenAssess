#include <stdio.h>

int power(int base, int exp, int mod) {
    if (exp == 0)
        return 1;
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return (int)result;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    int result = power(a, b, p);
    printf("%d^%d mod %d=%d\n", a, b, p, result);
    return 0;
}