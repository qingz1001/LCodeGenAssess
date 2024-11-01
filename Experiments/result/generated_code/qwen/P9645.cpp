#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        if ((x + y - z) % y != 0) {
            printf("-1\n");
        } else {
            long long k = (x + y - z) / y + 1;
            if (k >= 1 && k <= 2 * 1000000000) {
                printf("%lld\n", k);
            } else {
                printf("-1\n");
            }
        }
    }
    return 0;
}