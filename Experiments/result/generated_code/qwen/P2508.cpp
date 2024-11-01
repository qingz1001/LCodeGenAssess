#include <stdio.h>
#include <math.h>

int main() {
    long long r;
    scanf("%lld", &r);
    int count = 0;
    for (long long x = -r; x <= r; x++) {
        long long y_squared = r * r - x * x;
        if (y_squared >= 0) {
            long long y = sqrt(y_squared);
            if (y * y == y_squared) {
                count += (x % 2 == 0 ? 4 : 4);
            }
        }
    }
    printf("%d\n", count / 4);
    return 0;
}