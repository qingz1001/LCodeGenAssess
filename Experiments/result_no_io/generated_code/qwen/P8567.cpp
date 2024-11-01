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
    for (int i = 0; i < T; i++) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        int count = 0;
        for (long long j = l; j <= r - 1; j++) {
            if (f(j) < f(j + 1)) {
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}