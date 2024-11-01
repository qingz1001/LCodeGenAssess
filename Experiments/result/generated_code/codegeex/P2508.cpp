#include <stdio.h>
#include <math.h>

int main() {
    long long r;
    scanf("%lld", &r);
    long long ans = 0;

    for (long long i = 1; i * i <= r; i++) {
        if (r % i == 0) {
            long long j = r / i;
            if (i % 2 == 0) {
                ans++;
            }
            if (j % 2 == 0 && j != i) {
                ans++;
            }
        }
    }

    printf("%lld\n", ans * 4);
    return 0;
}