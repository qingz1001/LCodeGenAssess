#include <stdio.h>

// 定义工作结构体
typedef struct {
    int time_required;
    int deadline;
} Job;

// 比较函数，用于按截止时间排序
int compare(const void *a, const void *b) {
    Job *job_a = (Job *)a;
    Job *job_b = (Job *)b;
    return job_a->deadline - job_b->deadline;
}

int main() {
    int N;
    scanf("%d", &N);

    Job jobs[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jobs[i].time_required, &jobs[i].deadline);
    }

    // 按截止时间排序
    qsort(jobs, N, sizeof(Job), compare);

    int current_time = 0;
    for (int i = 0; i < N; i++) {
        // 如果当前时间加上完成这个工作的时间超过了截止时间，则无法完成所有工作
        if (current_time + jobs[i].time_required > jobs[i].deadline) {
            printf("-1\n");
            return 0;
        }
        current_time += jobs[i].time_required;
    }

    // 如果所有工作都能按时完成，则输出最迟开始工作时间
    printf("%d\n", current_time);
    return 0;
}