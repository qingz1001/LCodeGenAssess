#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 100

typedef struct {
    int time;
    int prereq[MAXM];
    int prereq_count;
} Task;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    Task tasks[MAXN];
    int finish_time[MAXN] = {0};

    for (int i = 0; i < n; i++) {
        int task_id, time;
        scanf("%d %d", &task_id, &time);
        tasks[i].time = time;
        tasks[i].prereq_count = 0;

        int prereq;
        while (scanf("%d", &prereq) && prereq != 0) {
            tasks[i].prereq[tasks[i].prereq_count++] = prereq - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        int max_prereq_time = 0;
        for (int j = 0; j < tasks[i].prereq_count; j++) {
            max_prereq_time = max(max_prereq_time, finish_time[tasks[i].prereq[j]]);
        }
        finish_time[i] = max_prereq_time + tasks[i].time;
    }

    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time = max(total_time, finish_time[i]);
    }

    printf("%d\n", total_time);

    return 0;
}