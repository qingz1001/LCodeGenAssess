#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int time;
    int deadline;
} Job;

int compare(const void *a, const void *b) {
    return ((Job *)a)->deadline - ((Job *)b)->deadline;
}

int main() {
    int N;
    Job jobs[MAX_N];

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jobs[i].time, &jobs[i].deadline);
    }

    qsort(jobs, N, sizeof(Job), compare);

    int current_time = 0;
    int latest_start = 0;

    for (int i = 0; i < N; i++) {
        current_time += jobs[i].time;
        if (current_time > jobs[i].deadline) {
            printf("-1\n");
            return 0;
        }
        if (jobs[i].deadline - current_time > latest_start) {
            latest_start = jobs[i].deadline - current_time;
        }
    }

    printf("%d\n", latest_start);

    return 0;
}