#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
    int start;
    int end;
    int priority;
} Task;

int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    if (taskA->priority != taskB->priority) {
        return taskA->priority - taskB->priority;
    } else if (taskA->end != taskB->end) {
        return taskA->end - taskB->end;
    } else {
        return taskA->start - taskB->start;
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    Task tasks[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].start, &tasks[i].end, &tasks[i].priority);
    }

    qsort(tasks, m, sizeof(Task), compare);

    int x, a, b, c;
    int pre = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x, &a, &b, &c);
        int k = 1 + (a * pre + b) % c;

        int sum = 0;
        int count = 0;
        for (int j = 0; j < m; j++) {
            if (tasks[j].start <= x && tasks[j].end > x) {
                sum += tasks[j].priority;
                count++;
                if (count == k) {
                    break;
                }
            }
        }

        pre = sum;
        printf("%d\n", pre);
    }

    return 0;
}