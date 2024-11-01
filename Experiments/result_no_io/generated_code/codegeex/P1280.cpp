#include <stdio.h>
#include <stdlib.h>

typedef struct Task {
    int start;
    int duration;
} Task;

int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
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

    int dp[n + 1];
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int j = 0; j < k; j++) {
            if (tasks[j].start <= i && i <= tasks[j].start + tasks[j].duration - 1) {
                dp[i] = (dp[i] > dp[tasks[j].start - 1]) ? dp[i] : dp[tasks[j].start - 1];
            }
        }
        if (dp[i] == 0 && i != n) {
            dp[i] = dp[i - 1] + 1;
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}