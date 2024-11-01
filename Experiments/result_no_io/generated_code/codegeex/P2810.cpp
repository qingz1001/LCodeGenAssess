#include <stdio.h>
#include <math.h>

long long n;

int main() {
    scanf("%lld", &n);
    long long i, j, k, l, m, ans = -1;

    for (i = 1; i <= 1000000000; i++) {
        for (j = 1; j <= i; j++) {
            if (i % j != 0) continue;
            for (k = 1; k <= j; k++) {
                if (j % k != 0) continue;
                for (l = 1; l <= k; l++) {
                    if (k % l != 0) continue;
                    if (i * j * k * l > n) break;
                    m = i * j * k * l;
                    if (m % n == 0) {
                        ans = m;
                        goto end;
                    }
                }
            }
        }
    }

end:
    printf("%lld\n", ans);
    return 0;
}