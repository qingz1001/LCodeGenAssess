#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100000

long long logs[MAX_L];

int check(long long n, int l, int k) {
    long long lines = 0;
    int ac_count = 0;
    for (int i = 0; i < l; i++) {
        lines += logs[i];
        if (lines < 0) lines = 0;
        if (lines >= n) {
            ac_count++;
            lines = 0;
        }
    }
    return ac_count;
}

void find_n(int l, int k) {
    long long left = 1, right = 1e18;
    long long min_n = -1, max_n = -1;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (check(mid, l, k) <= k) {
            right = mid - 1;
            if (check(mid, l, k) == k) {
                min_n = mid;
            }
        } else {
            left = mid + 1;
        }
    }

    left = 1, right = 1e18;
    while (left <= right) {
        long long mid = (left + right) / 2;
        if (check(mid, l, k) >= k) {
            left = mid + 1;
            if (check(mid, l, k) == k) {
                max_n = mid;
            }
        } else {
            right = mid - 1;
        }
    }

    if (min_n == -1 || max_n == -1) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", min_n, max_n);
    }
}

int main() {
    int l, k;
    scanf("%d %d", &l, &k);
    for (int i = 0; i < l; i++) {
        scanf("%lld", &logs[i]);
    }
    find_n(l, k);
    return 0;
}