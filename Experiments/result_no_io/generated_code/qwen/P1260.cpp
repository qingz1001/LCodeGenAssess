#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 5000
#define INF 1000000000

int n, m;
int T[MAX_N];
int graph[MAX_N][MAX_N];

void dfs(int node, int time, int *visited, int *min_time) {
    if (visited[node]) return;
    visited[node] = 1;
    T[node] = time;

    for (int i = 0; i < n; i++) {
        if (graph[node][i] != -1 && T[i] == -1) {
            dfs(i, time + graph[node][i], visited, min_time);
        }
    }

    *min_time = (*min_time > time) ? time : *min_time;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, b;
        scanf("%d %d %d", &u, &v, &b);
        graph[v-1][u-1] = b;
    }

    int visited[MAX_N] = {0};
    int min_time = INF;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, 0, visited, &min_time);
        }
    }

    for (int i = 0; i < n; i++) {
        if (T[i] == -1) {
            printf("NO SOLUTION\n");
            return 0;
        }
    }

    int offset = min_time;
    for (int i = 0; i < n; i++) {
        T[i] -= offset;
    }

    if (T[0] != 0) {
        printf("NO SOLUTION\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", T[i]);
    }

    return 0;
}