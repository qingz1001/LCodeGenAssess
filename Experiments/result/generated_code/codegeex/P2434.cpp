#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    if (intervalA->start == intervalB->start) {
        return intervalA->end - intervalB->end;
    }
    return intervalA->start - intervalB->start;
}

int main() {
    int n;
    scanf("%d", &n);

    Interval intervals[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, n, sizeof(Interval), compare);

    Interval mergedIntervals[50000];
    int count = 0;
    mergedIntervals[count++] = intervals[0];

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= mergedIntervals[count - 1].end) {
            if (intervals[i].end > mergedIntervals[count - 1].end) {
                mergedIntervals[count - 1].end = intervals[i].end;
            }
        } else {
            mergedIntervals[count++] = intervals[i];
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d %d\n", mergedIntervals[i].start, mergedIntervals[i].end);
    }

    return 0;
}