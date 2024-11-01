#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        
        long long k = (x + y) - z;
        
        if (k > 0 && k > x && k > z && (x + y) % k == z % k) {
            printf("%lld\n", k);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}