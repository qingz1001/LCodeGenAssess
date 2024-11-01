#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int l, r;
} Interval;

int compareIntervals(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    return (ia->l != ib->l) ? (ia->l - ib->l) : (ia->r - ib->r);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Interval intervals[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    qsort(intervals, n, sizeof(Interval), compareIntervals);

    int minCost = INT_MAX;
    for (int i = 0; i <= n - m; i++) {
        int maxR = intervals[i].r;
        int minR = intervals[i].r;
        int count = 1;

        for (int j = i + 1; j < n && count < m; j++) {
            if (intervals[j].l <= maxR) {
                maxR = (intervals[j].r > maxR) ? intervals[j].r : maxR;
                minR = (intervals[j].r < minR) ? intervals[j].r : minR;
                count++;
            } else {
                break;
            }
        }

        if (count == m) {
            int cost = maxR - minR;
            minCost = (cost < minCost) ? cost : minCost;
        }
    }

    if (minCost == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minCost);
    }

    return 0;
}