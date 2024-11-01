#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Contest;

int compare(const void *a, const void *b) {
    Contest *contestA = (Contest *)a;
    Contest *contestB = (Contest *)b;
    return contestA->end - contestB->end;
}

int main() {
    int n;
    scanf("%d", &n);
    Contest contests[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &contests[i].start, &contests[i].end);
    }

    qsort(contests, n, sizeof(Contest), compare);

    int count = 0;
    int lastEnd = -1;

    for (int i = 0; i < n; i++) {
        if (contests[i].start >= lastEnd) {
            count++;
            lastEnd = contests[i].end;
        }
    }

    printf("%d\n", count);

    return 0;
}