#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int deadline;
} Job;

int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return jobB->deadline - jobA->deadline;
}

int main() {
    int N;
    scanf("%d", &N);

    Job jobs[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jobs[i].time, &jobs[i].deadline);
    }

    // Sort jobs by their deadlines in descending order
    qsort(jobs, N, sizeof(Job), compare);

    int latestStartTime = jobs[0].deadline - jobs[0].time;

    for (int i = 1; i < N; i++) {
        if (latestStartTime > jobs[i].deadline) {
            latestStartTime = jobs[i].deadline;
        }
        latestStartTime -= jobs[i].time;
    }

    if (latestStartTime < 0) {
        printf("-1\n");
    } else {
        printf("%d\n", latestStartTime);
    }

    return 0;
}