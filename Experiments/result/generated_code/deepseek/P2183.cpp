#include <stdio.h>

#define MAX_M 5

long long mod_inv(long long a, long long p) {
    long long m = p, t, q;
    long long x = 0, y = 1;
    if (p == 1) return 0;
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p;
        a = t;
        t = x;
        x = y - q * x;
        y = t;
    }
    if (y < 0) y += m;
    return y;
}

long long mod_factorial(long long n, long long p) {
    long long result = 1;
    while (n > 1) {
        result = (result * ((n / p) % 2 ? p - 1 : 1)) % p;
        for (long long i = 2; i <= n % p; ++i) {
            result = (result * i) % p;
        }
        n /= p;
    }
    return result % p;
}

long long mod_combination(long long n, long long k, long long p) {
    if (n < k) return 0;
    if (k == 0) return 1;
    return (mod_factorial(n, p) * mod_inv((mod_factorial(k, p) * mod_factorial(n - k, p)) % p, p)) % p;
}

int main() {
    long long P, n, m;
    long long w[MAX_M];

    scanf("%lld", &P);
    scanf("%lld %lld", &n, &m);
    long long total_w = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &w[i]);
        total_w += w[i];
    }

    if (total_w > n) {
        printf("Impossible\n");
        return 0;
    }

    long long result = 1;
    long long remaining = n;
    for (int i = 0; i < m; ++i) {
        result = (result * mod_combination(remaining, w[i], P)) % P;
        remaining -= w[i];
    }

    printf("%lld\n", result);
    return 0;
}