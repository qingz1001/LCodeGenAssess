#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define MAXM 100005

typedef struct {
    int u, v, t;
} Edge;

typedef struct {
    int k, u, v;
} Task;

int n, m, q;
Edge edges[MAXM];
Task tasks[MAXM];
int graph[MAXN][MAXN];

void dijkstra(int start, int end) {
    int dist[MAXN];
    int visited[MAXN];
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int minDist = INT_MAX, minIndex = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        if (minIndex == -1) break;
        visited[minIndex] = 1;

        for (int j = 1; j <= n; j++) {
            if (!visited[j] && graph[minIndex][j] != INT_MAX && dist[minIndex] + graph[minIndex][j] < dist[j]) {
                dist[j] = dist[minIndex] + graph[minIndex][j];
            }
        }
    }

    if (dist[end] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[end]);
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        edges[i] = (Edge){u, v, t};
        graph[u][v] = graph[v][u] = t;
    }

    for (int i = 0; i < q; i++) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        tasks[i] = (Task){k, u, v};
        if (k == 2) {
            graph[u][v] = graph[v][u] = INT_MAX;
        }
    }

    for (int i = 0; i < q; i++) {
        if (tasks[i].k == 1) {
            dijkstra(tasks[i].u, tasks[i].v);
        }
    }

    return 0;
}