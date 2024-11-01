#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100000

long long logs[MAX_L];

int check(long long n, int l, int k) {
    long long current = 0;
    int count = 0;
    for (int i = 0; i < l; i++) {
        current += logs[i];
        if (current < 0) current = 0;
        if (current >= n) {
            count++;
            current = 0;
        }
    }
    return count;
}

int main() {
    int l, k;
    scanf("%d %d", &l, &k);
    for (int i = 0; i < l; i++) {
        scanf("%lld", &logs[i]);
    }

    long long low = 1, high = 1e18;
    long long min_n = -1, max_n = -1;

    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(mid, l, k) <= k) {
            if (check(mid, l, k) == k) {
                min_n = mid;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    low = 1, high = 1e18;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(mid, l, k) >= k) {
            if (check(mid, l, k) == k) {
                max_n = mid;
            }
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (min_n == -1 || max_n == -1) {
        printf("-1\n");
    } else {
        printf("%lld %lld\n", min_n, max_n);
    }

    return 0;
}