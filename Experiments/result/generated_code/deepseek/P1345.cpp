#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 105
#define MAXM 605

int N, M, c1, c2;
int graph[MAXN][MAXN];
int visited[MAXN];
int parent[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs() {
    int queue[MAXN];
    int front = 0, rear = 0;
    for (int i = 1; i <= N; i++) {
        visited[i] = 0;
    }
    queue[rear++] = c1;
    visited[c1] = 1;
    parent[c1] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= N; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }
    return visited[c2];
}

int fordFulkerson() {
    int max_flow = 0;
    while (bfs()) {
        int path_flow = INT_MAX;
        for (int v = c2; v != c1; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }

        for (int v = c2; v != c1; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    scanf("%d %d %d %d", &N, &M, &c1, &c2);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int min_cut = fordFulkerson();
    printf("%d\n", min_cut);

    return 0;
}