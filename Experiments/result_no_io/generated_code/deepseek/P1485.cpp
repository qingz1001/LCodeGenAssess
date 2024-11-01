#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

int n, k;
long long m[MAXN];

int check(long long p) {
    long long bullets_needed = 0;
    for (int i = 0; i < n; i++) {
        long long direct_damage = p;
        long long total_damage = direct_damage;
        for (int j = i - 1; j >= 0; j--) {
            long long splash_damage = direct_damage - (i - j) * (i - j);
            if (splash_damage <= 0) break;
            total_damage += splash_damage;
        }
        if (total_damage < m[i]) {
            bullets_needed += (m[i] - total_damage + p - 1) / p;
            if (bullets_needed > k) return 0;
        }
    }
    return 1;
}

long long binary_search(long long left, long long right) {
    while (left < right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }

    long long max_health = 0;
    for (int i = 0; i < n; i++) {
        if (m[i] > max_health) {
            max_health = m[i];
        }
    }

    long long result = binary_search(1, max_health);
    printf("%lld\n", result);

    return 0;
}