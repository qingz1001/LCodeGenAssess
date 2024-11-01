#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        long long a0, a1, b0, b1;
        scanf("%lld %lld %lld %lld", &a0, &a1, &b0, &b1);
        if (a0 % a1 != 0 || b1 % b0 != 0) {
            printf("0\n");
            continue;
        }
        long long x_min = a1 * b0;
        long long x_max = a0 * b1;
        long long common_divisor = gcd(x_min, x_max);
        long long count = 0;
        for (long long x = x_min; x <= x_max; x += common_divisor) {
            if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}