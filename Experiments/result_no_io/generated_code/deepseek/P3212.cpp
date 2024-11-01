#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20

typedef struct {
    int type;
    int a;
    int b;
} Task;

int n;
Task tasks[MAXN];
int min_time = INT_MAX;

void dfs(int idx, int timeA, int timeB, int mask) {
    if (idx == n) {
        int max_time = timeA > timeB ? timeA : timeB;
        if (max_time < min_time) {
            min_time = max_time;
        }
        return;
    }

    Task task = tasks[idx];

    if (task.type == 1) {
        dfs(idx + 1, timeA + task.a, timeB > timeA ? timeB : timeA + task.b, mask);
    } else if (task.type == 2) {
        dfs(idx + 1, timeA > timeB ? timeA : timeB + task.a, timeB + task.b, mask);
    } else {
        if (!(mask & (1 << idx))) {
            dfs(idx + 1, timeA + task.a, timeB > timeA ? timeB : timeA + task.b, mask | (1 << idx));
            dfs(idx + 1, timeA > timeB ? timeA : timeB + task.a, timeB + task.b, mask | (1 << idx));
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &tasks[i].type, &tasks[i].a, &tasks[i].b);
    }

    dfs(0, 0, 0, 0);

    printf("%d\n", min_time);

    return 0;
}