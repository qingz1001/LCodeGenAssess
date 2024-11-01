#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int start;
    int end;
    int priority;
} Task;

typedef struct {
    int time;
    int a;
    int b;
    int c;
} Query;

int compare(const void *a, const void *b) {
    return ((Task *)a)->start - ((Task *)b)->start;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    Task tasks[MAXM];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &tasks[i].start, &tasks[i].end, &tasks[i].priority);
    }

    Query queries[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &queries[i].time, &queries[i].a, &queries[i].b, &queries[i].c);
    }

    qsort(tasks, m, sizeof(Task), compare);

    int pre = 1;
    for (int i = 0; i < n; ++i) {
        int k = (1 + (queries[i].a * pre + queries[i].b) % queries[i].c) + 1;
        int current_time = queries[i].time;
        int task_count = 0;
        int sum = 0;

        for (int j = 0; j < m; ++j) {
            if (tasks[j].start <= current_time && tasks[j].end >= current_time) {
                ++task_count;
                sum += tasks[j].priority;
                if (task_count == k) break;
            }
        }

        printf("%d\n", sum);
        pre = sum;
    }

    return 0;
}