#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_B 1000000

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

int main() {
    int N;
    scanf("%d", &N);
    Interval intervals[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    qsort(intervals, N, sizeof(Interval), compare);

    int stalls[MAX_B + 1] = {0};
    int max_stalls = 0;

    for (int i = 0; i < N; ++i) {
        int start = intervals[i].start;
        int end = intervals[i].end;

        int assigned_stall = -1;
        for (int j = start; j <= end; ++j) {
            if (stalls[j] == 0) {
                assigned_stall = j;
                break;
            }
        }

        if (assigned_stall == -1) {
            assigned_stall = end + 1;
            for (int j = end + 1; j >= start; --j) {
                stalls[j]++;
            }
        } else {
            for (int j = start; j <= end; ++j) {
                stalls[j]++;
            }
        }

        max_stalls = assigned_stall > max_stalls ? assigned_stall : max_stalls;
    }

    printf("%d\n", max_stalls);
    for (int i = 0; i < N; ++i) {
        int start = intervals[i].start;
        int end = intervals[i].end;
        for (int j = start; j <= end; ++j) {
            if (stalls[j] == 1) {
                printf("%d\n", j);
                break;
            }
        }
    }

    return 0;
}