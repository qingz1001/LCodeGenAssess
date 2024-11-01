#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_PRE 100

int main() {
    int n;
    scanf("%d", &n);

    int time[MAX_N + 1];
    int pre[MAX_N + 1][MAX_PRE + 1];
    int indegree[MAX_N + 1] = {0};
    int dist[MAX_N + 1];

    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &time[i], &pre[i][0]);
        int j = 1;
        while (pre[i][j] != 0) {
            indegree[pre[i][j]]++;
            scanf("%d", &pre[i][++j]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            dist[i] = time[i];
        } else {
            dist[i] = -1;
        }
    }

    int count = 0;
    while (count < n) {
        int max_dist = -1;
        int next_task = -1;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] >= 0 && (next_task == -1 || dist[i] > max_dist)) {
                max_dist = dist[i];
                next_task = i;
            }
        }
        if (next_task == -1) break;

        dist[next_task] = -1;
        count++;

        for (int j = 1; pre[next_task][j] != 0; ++j) {
            indegree[pre[next_task][j]]--;
            if (indegree[pre[next_task][j]] == 0) {
                dist[pre[next_task][j]] = max_dist + time[pre[next_task][j]];
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > result) {
            result = dist[i];
        }
    }

    printf("%d\n", result);
    return 0;
}