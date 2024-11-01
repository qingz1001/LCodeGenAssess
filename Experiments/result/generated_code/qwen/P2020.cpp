#include <stdio.h>

int main() {
    long long n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);

    if (n == 1 || n == 2) {
        printf("1\n");
        return 0;
    }

    long long fib[3] = {1, 1, 0};
    for (long long i = 3; i <= n; ++i) {
        fib[2] = (fib[0] + fib[1]) % p;
        fib[0] = fib[1];
        fib[1] = fib[2];

        if (i >= k) {
            fib[2] = (fib[2] - ((i - k) >= 0 ? fib[(i - k) % 3] : 0) + p) % p;
        }
    }

    printf("%lld\n", fib[2]);
    return 0;
}