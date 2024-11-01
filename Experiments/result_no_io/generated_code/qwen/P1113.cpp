#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_PRE 100

typedef struct {
    int id;
    int time;
    int num_pre;
    int pre[MAX_PRE];
} Task;

int main() {
    int n;
    scanf("%d", &n);

    Task tasks[n + 1];
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &tasks[i].id, &tasks[i].time);
        tasks[i].num_pre = 0;
    }

    for (int i = 1; i <= n; ++i) {
        int pre_id;
        while (scanf("%d", &pre_id) && pre_id != 0) {
            tasks[pre_id].num_pre++;
            tasks[i].pre[tasks[i].num_pre - 1] = pre_id;
        }
    }

    int dp[n + 1];
    for (int i = 1; i <= n; ++i) {
        dp[i] = tasks[i].time;
        for (int j = 0; j < tasks[i].num_pre; ++j) {
            dp[i] = dp[i] > dp[tasks[i].pre[j]] + tasks[i].time ? dp[i] : dp[tasks[i].pre[j]] + tasks[i].time;
        }
    }

    int max_time = 0;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] > max_time) {
            max_time = dp[i];
        }
    }

    printf("%d\n", max_time);

    return 0;
}