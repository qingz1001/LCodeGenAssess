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
    scanf("%d %d", &n, &k);

    Task tasks[MAX_K];
    for (int i = 0; i < k; i++) {
        int p, t;
        scanf("%d %d", &p, &t);
        tasks[i].start = p;
        tasks[i].end = p + t - 1;
    }

    qsort(tasks, k, sizeof(Task), compare);

    int dp[MAX_N];
    memset(dp, 0, sizeof(dp));

    int last_end = 0;
    for (int i = 0; i < k; i++) {
        int start = tasks[i].start;
        int end = tasks[i].end;

        if (start > last_end) {
            dp[end] = dp[last_end] + (start - last_end - 1);
        } else {
            dp[end] = dp[last_end];
        }

        if (i > 0 && end > tasks[i-1].end) {
            dp[end] = (dp[end] > dp[tasks[i-1].end]) ? dp[end] : dp[tasks[i-1].end];
        }

        last_end = end;
    }

    int max_free_time = dp[last_end] + (n - last_end);
    printf("%d\n", max_free_time);

    return 0;
}