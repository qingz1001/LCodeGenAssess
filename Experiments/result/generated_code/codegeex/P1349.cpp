#include <stdio.h>

int main() {
    long long p, q, a1, a2, n, m;
    scanf("%lld %lld %lld %lld %lld %lld", &p, &q, &a1, &a2, &n, &m);

    if (n == 1) {
        printf("%lld\n", a1 % m);
        return 0;
    }
    if (n == 2) {
        printf("%lld\n", a2 % m);
        return 0;
    }

    long long an = a1, an1 = a2;
    for (long long i = 3; i <= n; i++) {
        long long temp = an1;
        an1 = (p * an1 + q * an) % m;
        an = temp;
    }

    printf("%lld\n", an1);
    return 0;
}