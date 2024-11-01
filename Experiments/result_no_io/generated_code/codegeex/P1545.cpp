#include <stdio.h>
#include <stdlib.h>

#define MAX_L 1000000
#define MAX_N 1000
#define MAX_A 1000
#define MAX_B 1000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    return intervalA->start - intervalB->start;
}

int main() {
    int N, L, A, B;
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    Interval intervals[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, N, sizeof(Interval), compare);

    int current_end = 0;
    int count = 0;

    for (int i = 0; i < N; i++) {
        if (intervals[i].start > current_end) {
            printf("-1\n");
            return 0;
        }

        int max_reach = current_end + B;
        int min_reach = current_end + A;

        if (intervals[i].end > max_reach) {
            count++;
            current_end = max_reach;
        } else if (intervals[i].end > min_reach) {
            count++;
            current_end = intervals[i].end;
        }
    }

    printf("%d\n", count);

    return 0;
}