#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_P 1e12
#define MAX_Z 1e9
#define MAX_A 1e4
#define MAX_B 1e4

int main() {
    int n;
    long long p;
    scanf("%d %lld", &n, &p);

    int z[MAX_N], a[MAX_N], b[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &z[i], &a[i], &b[i]);
    }

    long long left = 0, right = MAX_P / n;
    while (left < right) {
        long long mid = (left + right) / 2;
        long long total_power = 0;
        for (int i = 0; i < n; ++i) {
            if (mid <= z[i]) {
                total_power += (long long)a[i] * mid;
            } else {
                total_power += (long long)a[i] * z[i] + (long long)b[i] * (mid - z[i]);
            }
        }
        if (total_power >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);
    return 0;
}