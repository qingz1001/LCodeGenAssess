#include <stdio.h>

int f(long long x) {
    int ans = 0;
    while (x % 2 == 0) {
        x /= 2;
        ans += 1;
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        int count = 0;
        for (long long i = l; i < r; i++) {
            if (f(i) < f(i + 1)) {
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}