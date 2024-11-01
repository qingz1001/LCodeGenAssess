#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        long long ans = 0;
        for (long long i = l; i <= r; i++) {
            int count = 0;
            while (i % 2 == 0) {
                i /= 2;
                count++;
            }
            int count_next = 0;
            while ((i + 1) % 2 == 0) {
                (i + 1) /= 2;
                count_next++;
            }
            if (count < count_next) {
                ans++;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}