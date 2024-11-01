#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int time;
    int deadline;
} Job;

int compare(const void *a, const void *b) {
    return ((Job*)a)->deadline - ((Job*)b)->deadline;
}

int main() {
    int n;
    Job jobs[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &jobs[i].time, &jobs[i].deadline);
    }
    
    qsort(jobs, n, sizeof(Job), compare);
    
    int total_time = 0;
    int latest_start = 0;
    
    for (int i = 0; i < n; i++) {
        total_time += jobs[i].time;
        if (total_time > jobs[i].deadline) {
            printf("-1\n");
            return 0;
        }
        int current_latest = jobs[i].deadline - total_time;
        if (current_latest > latest_start) {
            latest_start = current_latest;
        }
    }
    
    printf("%d\n", latest_start);
    
    return 0;
}