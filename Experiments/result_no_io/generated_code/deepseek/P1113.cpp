#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_PRE 100

typedef struct {
    int time;
    int pre[MAX_PRE];
    int pre_count;
} Task;

int main() {
    int n;
    scanf("%d", &n);

    Task tasks[MAX_N];
    int max_time[MAX_N] = {0};

    for (int i = 0; i < n; i++) {
        int task_id, time;
        scanf("%d %d", &task_id, &time);
        tasks[task_id - 1].time = time;
        tasks[task_id - 1].pre_count = 0;

        int pre_task;
        while (scanf("%d", &pre_task) && pre_task != 0) {
            tasks[task_id - 1].pre[tasks[task_id - 1].pre_count++] = pre_task - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        int max_pre_time = 0;
        for (int j = 0; j < tasks[i].pre_count; j++) {
            int pre_task = tasks[i].pre[j];
            if (max_time[pre_task] > max_pre_time) {
                max_pre_time = max_time[pre_task];
            }
        }
        max_time[i] = max_pre_time + tasks[i].time;
    }

    int total_max_time = 0;
    for (int i = 0; i < n; i++) {
        if (max_time[i] > total_max_time) {
            total_max_time = max_time[i];
        }
    }

    printf("%d\n", total_max_time);

    return 0;
}