#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time_required;
    int deadline;
} Job;

int compare(const void *a, const void *b) {
    Job *job_a = (Job *)a;
    Job *job_b = (Job *)b;
    return job_a->deadline - job_b->deadline;
}

int main() {
    int N;
    scanf("%d", &N);

    Job jobs[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jobs[i].time_required, &jobs[i].deadline);
    }

    qsort(jobs, N, sizeof(Job), compare);

    int current_time = 0;
    for (int i = 0; i < N; i++) {
        if (current_time + jobs[i].time_required > jobs[i].deadline) {
            printf("-1\n");
            return 0;
        }
        current_time += jobs[i].time_required;
    }

    printf("%d\n", current_time);
    return 0;
}