#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

int main() {
    int n;
    Interval intervals[MAX_N];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, n, sizeof(Interval), compare);

    int current_end = intervals[0].end;
    int current_start = intervals[0].start;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= current_end) {
            if (intervals[i].end > current_end) {
                current_end = intervals[i].end;
            }
        } else {
            printf("%d %d\n", current_start, current_end);
            current_start = intervals[i].start;
            current_end = intervals[i].end;
        }
    }
    printf("%d %d\n", current_start, current_end);

    return 0;
}