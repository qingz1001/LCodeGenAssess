#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct {
    int l, r;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->l - ((Interval *)b)->l;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Interval intervals[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    qsort(intervals, n, sizeof(Interval), compare);

    int left = intervals[0].l, right = intervals[0].r;
    int min_cost = INT_MAX;

    for (int i = 1; i <= m; i++) {
        if (right >= intervals[i].l) {
            right = (right > intervals[i].r) ? right : intervals[i].r;
        } else {
            if (min_cost == INT_MAX) {
                min_cost = right - left;
            }
            left = intervals[i].l;
            right = intervals[i].r;
        }
    }

    if (min_cost == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", right - left);
    }

    return 0;
}