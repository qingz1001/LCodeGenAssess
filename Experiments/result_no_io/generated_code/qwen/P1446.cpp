#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res = (res * i) % MOD;
    }
    return res;
}

int main() {
    int Sr, Sb, Sg, m, P;
    scanf("%d %d %d %d %d", &Sr, &Sb, &Sg, &m, &P);

    long long total_ways = factorial(Sr + Sb + Sg);
    total_ways = (total_ways * mod_inverse(factorial(Sr), P)) % P;
    total_ways = (total_ways * mod_inverse(factorial(Sb), P)) % P;
    total_ways = (total_ways * mod_inverse(factorial(Sg), P)) % P;

    printf("%lld\n", total_ways);
    return 0;
}