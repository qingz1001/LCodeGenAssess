#include <stdio.h>

int main() {
    long long p, q, a1, a2, n, m;
    scanf("%lld %lld %lld %lld %lld %lld", &p, &q, &a1, &a2, &n, &m);

    if (n == 1) {
        printf("%lld\n", a1 % m);
        return 0;
    } else if (n == 2) {
        printf("%lld\n", a2 % m);
        return 0;
    }

    long long an_minus_2 = a1;
    long long an_minus_1 = a2;
    long long an;

    for (long long i = 3; i <= n; i++) {
        an = (p * an_minus_1 + q * an_minus_2) % m;
        an_minus_2 = an_minus_1;
        an_minus_1 = an;
    }

    printf("%lld\n", an);
    return 0;
}