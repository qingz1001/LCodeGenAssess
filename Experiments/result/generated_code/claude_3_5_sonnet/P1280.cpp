#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_K 10001

typedef struct {
    int start;
    int end;
} Task;

int compare(const void *a, const void *b) {
    return ((Task *)a)->end - ((Task *)b)->end;
}

int main() {
    int n, k;
    Task tasks[MAX_K];
    int dp[MAX_N] = {0};

    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; i++) {
        int p, t;
        scanf("%d %d", &p, &t);
        tasks[i].start = p;
        tasks[i].end = p + t - 1;
    }

    qsort(tasks, k, sizeof(Task), compare);

    int max_free_time = 0;
    for (int i = 0; i < k; i++) {
        int free_time = (i > 0 ? dp[tasks[i-1].end] : 0) + (tasks[i].start - 1) - (i > 0 ? tasks[i-1].end : 0);
        dp[tasks[i].end] = (i > 0 ? dp[tasks[i-1].end] : 0) + free_time;
        if (dp[tasks[i].end] > max_free_time) {
            max_free_time = dp[tasks[i].end];
        }
    }

    max_free_time += n - tasks[k-1].end;

    printf("%d\n", max_free_time);

    return 0;
}