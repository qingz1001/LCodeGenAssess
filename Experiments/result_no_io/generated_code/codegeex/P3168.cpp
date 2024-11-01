#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int r;
    int priority;
} Task;

int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    if (taskA->priority != taskB->priority) {
        return taskA->priority - taskB->priority;
    } else {
        return taskA->l - taskB->l;
    }
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    Task tasks[m];
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &tasks[i].l, &tasks[i].r, &tasks[i].priority);
    }

    qsort(tasks, m, sizeof(Task), compare);

    int queries[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &queries[i]);
    }

    long long pre = 1;
    for (int i = 0; i < n; i++) {
        int x, a, b, c;
        scanf("%d%d%d%d", &x, &a, &b, &c);
        int k = 1 + (a * pre + b) % c;

        long long sum = 0;
        int count = 0;
        for (int j = 0; j < m; j++) {
            if (tasks[j].l <= x && tasks[j].r > x) {
                sum += tasks[j].priority;
                count++;
                if (count == k) {
                    break;
                }
            }
        }

        printf("%lld\n", sum);
        pre = sum;
    }

    return 0;
}