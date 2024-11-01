#include <stdio.h>

#define MOD 1000000007

long long power(long long x, long long y) {
    long long res = 1;
    x = x % MOD;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % MOD;
        y = y >> 1;
        x = (x * x) % MOD;
    }
    return res;
}

int main() {
    long long n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);

    if (n == 1 || n == 2) {
        printf("1\n");
        return 0;
    }

    long long a[3] = {1, 1, 2};
    for (long long i = 3; i <= n; ++i) {
        long long next = (a[(i - 1) % 3] + a[(i - 2) % 3]) % MOD;
        while (next >= k) {
            next -= k;
        }
        a[i % 3] = next;
    }

    printf("%lld\n", a[n % 3]);

    return 0;
}