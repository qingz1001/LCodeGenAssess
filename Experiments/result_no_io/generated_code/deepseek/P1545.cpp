#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_L 1000000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    return ia->start - ib->start;
}

int main() {
    int N, L;
    int A, B;
    Interval intervals[MAX_N];

    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, N, sizeof(Interval), compare);

    int current_end = 0;
    int sprinklers = 0;
    int i = 0;

    while (current_end < L) {
        int max_end = current_end;
        while (i < N && intervals[i].start <= current_end) {
            if (intervals[i].end > max_end) {
                max_end = intervals[i].end;
            }
            i++;
        }

        if (max_end == current_end) {
            printf("-1\n");
            return 0;
        }

        current_end = max_end;
        sprinklers++;
    }

    printf("%d\n", sprinklers);
    return 0;
}