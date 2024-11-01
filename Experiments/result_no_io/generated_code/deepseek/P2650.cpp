#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compareIntervals(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    return intervalA->start - intervalB->start;
}

int countOverlaps(Interval *intervals, int n, int queryStart, int queryEnd) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (intervals[i].end > queryStart && intervals[i].start < queryEnd) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Interval *intervals = (Interval *)malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        intervals[i].start = a;
        intervals[i].end = a + b;
    }

    // Sort intervals by start time
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int queryStart = x;
        int queryEnd = x + y;
        int result = countOverlaps(intervals, n, queryStart, queryEnd);
        printf("%d\n", result);
    }

    free(intervals);
    return 0;
}