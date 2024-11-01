#include <stdio.h>

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    long long r;
    scanf("%lld", &r);

    long long count = 0;
    for (long long x = 1; x <= r; x++) {
        long long y = r * r - x * x;
        long long sq = (long long)sqrt(y);
        if (sq * sq == y) {
            count += 4;
        }
    }

    if (r * r % 2 == 0) {
        count -= 4;
    }

    printf("%lld\n", count + 4);

    return 0;
}