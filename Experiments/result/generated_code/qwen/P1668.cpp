#include <stdio.h>
#include <stdlib.h>

#define MAX_T 1000000
#define MAX_N 25000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->end - ((Interval *)b)->end;
}

int main() {
    int N, T;
    scanf("%d %d", &N, &T);

    Interval intervals[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, N, sizeof(Interval), compare);

    int last_end = 0;
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (intervals[i].start > last_end) {
            count++;
            last_end = intervals[i].end;
        }
    }

    if (last_end < T) {
        printf("-1\n");
    } else {
        printf("%d\n", count);
    }

    return 0;
}