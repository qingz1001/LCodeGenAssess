#include <stdio.h>
#include <stdlib.h>

// 定义任务结构体
typedef struct {
    int start;
    int duration;
} Task;

// 比较函数，用于qsort排序
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

    // 按开始时间排序
    qsort(tasks, k, sizeof(Task), compare);

    // 定义dp数组，dp[i]表示从第i分钟开始的最大空闲时间
    int dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }

    // 倒序遍历每个时间点
    for (int i = n; i >= 1; i--) {
        int maxFreeTime = 0;
        // 遍历所有任务，找到在当前时间点i之前且结束时间不超过i的任务
        for (int j = 0; j < k; j++) {
            if (tasks[j].start < i && tasks[j].start + tasks[j].duration - 1 <= i) {
                // 更新dp[i]，选择结束时间最晚的任务
                maxFreeTime = (maxFreeTime > dp[tasks[j].start + tasks[j].duration]) ? maxFreeTime : dp[tasks[j].start + tasks[j].duration];
            }
        }
        // 更新dp[i]，加上当前时间点的空闲时间
        dp[i] = maxFreeTime + 1;
    }

    // 输出结果
    printf("%d\n", dp[1]);
    return 0;
}