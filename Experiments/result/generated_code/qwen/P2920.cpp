#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int deadline;
} Job;

int compare(const void *a, const void *b) {
    return ((Job *)b)->deadline - ((Job *)a)->deadline;
}

int main() {
    int N;
    scanf("%d", &N);
    Job jobs[N];
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jobs[i].time, &jobs[i].deadline);
    }
    
    qsort(jobs, N, sizeof(Job), compare);
    
    int currentTime = 0;
    for (int i = 0; i < N; i++) {
        if (currentTime + jobs[i].time > jobs[i].deadline) {
            printf("-1\n");
            return 0;
        }
        currentTime += jobs[i].time;
    }
    
    printf("%d\n", currentTime - jobs[N-1].time);
    return 0;
}