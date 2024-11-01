#include <stdio.h>
#include <math.h>

int main() {
    long long r;
    scanf("%lld", &r);

    long long count = 0;
    for (long long x = 1; x * x <= r; x++) {
        long long y2 = r * r - x * x;
        long long y = (long long)sqrt(y2);
        if (y * y == y2) {
            count += 2; // x, y 和 -x, -y 都是整数点
        }
    }

    printf("%lld\n", count);
    return 0;
}