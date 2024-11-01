#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long total = 0;
    for (int i = 1; i <= n; i++) {
        total += (long long)m * i;
        total %= MOD;
    }

    long long result = total * modInverse(n + 1, MOD);
    result %= MOD;

    printf("%lld\n", result);

    return 0;
}

long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}