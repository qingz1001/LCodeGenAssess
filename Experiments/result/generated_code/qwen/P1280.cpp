#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10005

typedef struct {
    int start;
    int duration;
} Task;

int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    if (taskA->start == taskB->start)
        return taskA->duration - taskB->duration;
    return taskA->start - taskB->start;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Task tasks[k];
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &tasks[i].start, &tasks[i].duration);
    }

    qsort(tasks, k, sizeof(Task), compare);

    int maxIdleTime = 0;
    int currentTime = 1;

    for (int i = 0; i < k; i++) {
        if (currentTime < tasks[i].start) {
            maxIdleTime += tasks[i].start - currentTime;
        }
        currentTime = tasks[i].start + tasks[i].duration;
    }

    if (currentTime <= n) {
        maxIdleTime += n - currentTime;
    }

    printf("%d\n", maxIdleTime);

    return 0;
}