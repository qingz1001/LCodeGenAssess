#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

long long n, k;
long long m[MAXN];

int main() {
    scanf("%lld %lld", &n, &k);
    for (long long i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }

    long long left = 0, right = 1e10;
    while (left < right) {
        long long mid = (left + right) / 2;
        long long bullets = 0;
        for (long long i = 0; i < n; i++) {
            if (m[i] > 0) {
                bullets += (m[i] + mid - 1) / mid;
                if (bullets > k) break;
            }
        }
        if (bullets <= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);

    return 0;
}