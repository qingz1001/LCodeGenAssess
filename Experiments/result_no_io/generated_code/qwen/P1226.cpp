#include <stdio.h>

int powerMod(int a, int b, int p) {
    if (p == 1) return 0;
    long long res = 1;
    a = a % p;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % p;
        b = b >> 1;
        a = (a * a) % p;
    }
    return (int)res;
}

int main() {
    int a, b, p;
    scanf("%d %d %d", &a, &b, &p);
    int result = powerMod(a, b, p);
    printf("%d^%d mod %d=%d\n", a, b, p, result);
    return 0;
}