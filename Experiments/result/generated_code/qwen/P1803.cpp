#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Event;

int compare(const void *a, const void *b) {
    return ((Event *)a)->end - ((Event *)b)->end;
}

int maxEvents(int n, Event events[]) {
    if (n == 0) return 0;

    qsort(events, n, sizeof(Event), compare);

    int count = 1;
    int lastEnd = events[0].end;

    for (int i = 1; i < n; i++) {
        if (events[i].start >= lastEnd) {
            count++;
            lastEnd = events[i].end;
        }
    }

    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    Event events[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &events[i].start, &events[i].end);
    }

    printf("%d\n", maxEvents(n, events));

    return 0;
}