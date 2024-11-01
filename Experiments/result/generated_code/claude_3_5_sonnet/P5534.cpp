#include <stdio.h>

int main() {
    long long a1, a2, n;
    scanf("%lld %lld %lld", &a1, &a2, &n);

    long long d = a2 - a1;  // 公差
    long long an = a1 + (n - 1) * d;  // 末项

    long long sum = (a1 + an) * n / 2;  // 等差数列求和公式

    printf("%lld\n", sum);

    return 0;
}