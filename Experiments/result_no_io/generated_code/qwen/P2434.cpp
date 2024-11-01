#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    if (intervalA->start != intervalB->start)
        return intervalA->start - intervalB->start;
    else
        return intervalA->end - intervalB->end;
}

int main() {
    int n;
    scanf("%d", &n);
    Interval intervals[MAXN];

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, n, sizeof(Interval), compare);

    int count = 0;
    Interval result[MAXN];
    result[count++] = intervals[0];

    for (int i = 1; i < n; ++i) {
        if (intervals[i].start > result[count - 1].end) {
            result[count++] = intervals[i];
        } else if (intervals[i].end > result[count - 1].end) {
            result[count - 1].end = intervals[i].end;
        }
    }

    for (int i = 0; i < count; ++i) {
        printf("%d %d\n", result[i].start, result[i].end);
    }

    return 0;
}