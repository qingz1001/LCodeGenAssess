#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    long long count = 0;

    for (long long x = 1; x <= n; ++x) {
        for (long long y = 1; y <= m; ++y) {
            if (gcd(x, y) == 1) {
                long long num = x * k - y;
                if (num > 0 && num % y == 0) {
                    count++;
                }
            }
        }
    }

    printf("%lld\n", count);
    return 0;
}