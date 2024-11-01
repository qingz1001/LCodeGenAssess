#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

long long monsters[MAXN];
int n, k;

int canKillAll(long long p) {
    long long bullets_needed = 0;
    for (int i = 0; i < n; i++) {
        long long direct_damage = p;
        long long total_damage = direct_damage;
        for (int j = i - 1; j >= 0; j--) {
            long long splash_damage = direct_damage - (i - j) * (i - j);
            if (splash_damage <= 0) break;
            total_damage += splash_damage;
        }
        bullets_needed += (monsters[i] + total_damage - 1) / total_damage; // ceiling of monsters[i] / total_damage
    }
    return bullets_needed <= k;
}

long long binarySearch(long long low, long long high) {
    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (canKillAll(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &monsters[i]);
    }

    long long max_hp = 0;
    for (int i = 0; i < n; i++) {
        if (monsters[i] > max_hp) {
            max_hp = monsters[i];
        }
    }

    long long result = binarySearch(1, max_hp);
    printf("%lld\n", result);

    return 0;
}