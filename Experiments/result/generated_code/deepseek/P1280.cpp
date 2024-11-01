#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }

    int taskIndex = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        while (taskIndex < k && tasks[taskIndex].start == i) {
            int endTime = tasks[taskIndex].start + tasks[taskIndex].duration - 1;
            dp[endTime] = dp[endTime] > dp[i - 1] ? dp[endTime] : dp[i - 1];
            taskIndex++;
        }
        dp[i] = dp[i] > dp[i - 1] + 1 ? dp[i] : dp[i - 1] + 1;
    }

    printf("%d\n", dp[n]);

    return 0;
}