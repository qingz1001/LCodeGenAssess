#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500000

typedef struct {
    int l, r;
} Interval;

Interval intervals[MAXN];
int n, m;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->l - ((Interval *)b)->l;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].l, &intervals[i].r);
    }

    qsort(intervals, n, sizeof(Interval), compare);

    int left = 0, right = 0;
    int min_cost = INT_MAX;
    int max_r = intervals[0].r;
    int count = 1;

    while (right < n) {
        while (right < n && count < m) {
            right++;
            if (right < n) {
                max_r = max(max_r, intervals[right].r);
                count++;
            }
        }

        if (count == m) {
            min_cost = min(min_cost, max_r - intervals[left].l);
        }

        count--;
        left++;
    }

    if (min_cost == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", min_cost);
    }

    return 0;
}