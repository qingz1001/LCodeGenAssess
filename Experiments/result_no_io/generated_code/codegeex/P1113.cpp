#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10000
#define MAX_PREDECESSORS 100

typedef struct {
    int duration;
    int num_predecessors;
    int *predecessors;
} Task;

int main() {
    int n;
    scanf("%d", &n);

    Task tasks[MAX_TASKS + 1];
    for (int i = 1; i <= n; i++) {
        int task_id, duration, num_predecessors, predecessor;
        scanf("%d %d", &task_id, &duration);
        tasks[task_id].duration = duration;
        tasks[task_id].num_predecessors = 0;
        tasks[task_id].predecessors = NULL;

        scanf("%d", &num_predecessors);
        while (num_predecessors != 0) {
            scanf("%d", &predecessor);
            tasks[task_id].num_predecessors++;
            tasks[task_id].predecessors = (int*)realloc(tasks[task_id].predecessors, tasks[task_id].num_predecessors * sizeof(int));
            tasks[task_id].predecessors[tasks[task_id].num_predecessors - 1] = predecessor;
            scanf("%d", &num_predecessors);
        }
    }

    int *earliest_start_time = (int*)calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < tasks[i].num_predecessors; j++) {
            earliest_start_time[i] = (earliest_start_time[i] > earliest_start_time[tasks[i].predecessors[j]]) ? earliest_start_time[i] : earliest_start_time[tasks[i].predecessors[j]];
        }
        earliest_start_time[i] += tasks[i].duration;
    }

    int max_time = 0;
    for (int i = 1; i <= n; i++) {
        if (earliest_start_time[i] > max_time) {
            max_time = earliest_start_time[i];
        }
    }

    printf("%d\n", max_time);

    for (int i = 1; i <= n; i++) {
        free(tasks[i].predecessors);
    }
    free(earliest_start_time);

    return 0;
}