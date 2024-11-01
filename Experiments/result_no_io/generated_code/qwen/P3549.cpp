#include <stdio.h>
#include <stdlib.h>

#define MAXN 500001

int n;
int graph[MAXN][2];
int visited[MAXN];

void dfs(int node, int prev, int steps, int *path, int *path_size) {
    if (node == n) {
        path[*path_size] = node;
        (*path_size)++;
        return;
    }
    visited[node] = 1;
    for (int i = 0; i < 2; i++) {
        int neighbor = graph[node][i];
        if (neighbor != prev && !visited[neighbor]) {
            if (steps <= 2) {
                path[*path_size] = node;
                (*path_size)++;
                dfs(neighbor, node, steps + 1, path, path_size);
                (*path_size)--;
            } else {
                dfs(neighbor, node, steps + 1, path, path_size);
            }
        }
    }
    visited[node] = 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        graph[i][0] = -1;
        graph[i][1] = -1;
    }

    int u, v;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &u, &v);
        if (graph[u][0] == -1) {
            graph[u][0] = v;
        } else {
            graph[u][1] = v;
        }
        if (graph[v][0] == -1) {
            graph[v][0] = u;
        } else {
            graph[v][1] = u;
        }
    }

    int path[MAXN];
    int path_size = 0;

    dfs(1, -1, 0, path, &path_size);

    if (path_size == n) {
        printf("1\n");
        for (int i = 0; i < path_size; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("BRAK\n");
    }

    return 0;
}