#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        long long k = (long long)x + y - z;
        if (k > 0 && k <= 2 * 1000000000) {
            printf("%lld\n", k);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}