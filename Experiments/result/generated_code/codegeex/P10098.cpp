#include <stdio.h>

long long n, p;
long long z[100], a[100], b[100];

int main() {
    scanf("%lld %lld", &n, &p);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &z[i], &a[i], &b[i]);
    }

    long long left = 1, right = 1e12;
    while (left < right) {
        long long mid = (left + right) / 2;
        long long power = 0;
        for (int i = 0; i < n; i++) {
            if (mid <= z[i]) {
                power += a[i] * z[i];
            } else {
                power += a[i] * z[i] + b[i] * (mid - z[i]);
            }
        }
        if (power >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    printf("%lld\n", left);
    return 0;
}