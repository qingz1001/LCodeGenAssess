#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

void mergeIntervals(Interval intervals[], int n) {
    if (n <= 0) return;

    qsort(intervals, n, sizeof(Interval), compare);

    int index = 0;
    for (int i = 1; i < n; i++) {
        if (intervals[index].end >= intervals[i].start) {
            intervals[index].end = (intervals[index].end > intervals[i].end) ? intervals[index].end : intervals[i].end;
        } else {
            intervals[++index] = intervals[i];
        }
    }

    for (int i = 0; i <= index; i++) {
        printf("%d %d\n", intervals[i].start, intervals[i].end);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Interval intervals[MAXN];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    mergeIntervals(intervals, n);

    return 0;
}