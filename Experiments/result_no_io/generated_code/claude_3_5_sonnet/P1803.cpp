#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Contest;

int compare(const void *a, const void *b) {
    return ((Contest *)a)->end - ((Contest *)b)->end;
}

int main() {
    int n;
    scanf("%d", &n);

    Contest *contests = malloc(n * sizeof(Contest));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &contests[i].start, &contests[i].end);
    }

    qsort(contests, n, sizeof(Contest), compare);

    int count = 0;
    int last_end = -1;

    for (int i = 0; i < n; i++) {
        if (contests[i].start >= last_end) {
            count++;
            last_end = contests[i].end;
        }
    }

    printf("%d\n", count);

    free(contests);
    return 0;
}