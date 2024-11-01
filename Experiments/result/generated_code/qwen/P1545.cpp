#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_L 1000000
#define MAX_A 1000
#define MAX_B 1000

int N, L;
int A, B;
struct Interval {
    int start, end;
} intervals[MAX_N];

int compare(const void *a, const void *b) {
    return ((struct Interval *)a)->start - ((struct Interval *)b)->start;
}

int main() {
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, N, sizeof(struct Interval), compare);

    int count = 0;
    int last_end = -1;

    for (int i = 0; i < N; i++) {
        if (intervals[i].start > last_end + 1) {
            count++;
            last_end = intervals[i].end + B;
        } else if (intervals[i].end > last_end) {
            last_end = intervals[i].end + B;
        }
    }

    printf("%d\n", count);

    return 0;
}