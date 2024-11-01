#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 600

int N, M, c1, c2;
int graph[MAX_N + 1][MAX_N + 1];
int visited[MAX_N + 1];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (graph[node][i]) dfs(i);
    }
}

int main() {
    scanf("%d %d %d %d", &N, &M, &c1, &c2);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int original_components = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i);
            original_components++;
        }
    }

    int removed_nodes = 0;
    for (int i = 1; i <= N; i++) {
        if (i != c1 && i != c2) {
            memset(visited, 0, sizeof(visited));
            graph[c1][i] = 0;
            graph[i][c1] = 0;
            graph[c2][i] = 0;
            graph[i][c2] = 0;
            int components = 0;
            for (int j = 1; j <= N; j++) {
                if (!visited[j]) {
                    dfs(j);
                    components++;
                }
            }
            if (components > original_components) {
                removed_nodes++;
                graph[c1][i] = 1;
                graph[i][c1] = 1;
                graph[c2][i] = 1;
                graph[i][c2] = 1;
            } else {
                graph[c1][i] = 0;
                graph[i][c1] = 0;
                graph[c2][i] = 0;
                graph[i][c2] = 0;
            }
        }
    }

    printf("%d\n", removed_nodes);

    return 0;
}