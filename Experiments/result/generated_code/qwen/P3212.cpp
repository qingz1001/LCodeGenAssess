#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

typedef struct {
    int type;
    int a_time;
    int b_time;
} Task;

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    int n;
    scanf("%d", &n);
    Task tasks[MAX_N];

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &tasks[i].type, &tasks[i].a_time, &tasks[i].b_time);
    }

    // Sort tasks by a_time + b_time in descending order
    qsort(tasks, n, sizeof(Task), [](const void *a, const void *b) {
        Task *ta = (Task *)a, *tb = (Task *)b;
        return (tb->a_time + tb->b_time) - (ta->a_time + ta->b_time);
    });

    int time_A = 0, time_B = 0;
    for (int i = 0; i < n; ++i) {
        if (tasks[i].type == 1) {
            time_A += tasks[i].a_time;
            time_B = max(time_B, time_A) + tasks[i].b_time;
        } else if (tasks[i].type == 2) {
            time_B += tasks[i].b_time;
            time_A = max(time_A, time_B) + tasks[i].a_time;
        } else {
            time_A += tasks[i].a_time;
            time_B += tasks[i].b_time;
        }
    }

    printf("%d\n", min(time_A, time_B));

    return 0;
}