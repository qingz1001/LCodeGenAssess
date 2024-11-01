#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 500005

typedef struct {
    int l, r;
} Interval;

Interval intervals[MAX_N];
int n, m;

int cmp(const void *a, const void *b) {
    return ((Interval*)a)->r - ((Interval*)b)->r;
}

int check(int diff) {
    int count = 0, last = -1;
    for (int i = 0; i < n && count < m; i++) {
        if (intervals[i].r - intervals[i].l <= diff && (last == -1 || intervals[i].l > last)) {
            count++;
            last = intervals[i].r;
        }
    }
    return count >= m;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    qsort(intervals, n, sizeof(Interval), cmp);

    int left = 0, right = 1000000000;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left == 1000000000) {
        printf("-1\n");
    } else {
        printf("%d\n", left);
    }

    return 0;
}