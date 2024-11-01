#include <stdio.h>
#include <stdlib.h>

#define MAX_N 105

int N, M, c1, c2;
int graph[MAX_N][MAX_N];
int visited[MAX_N];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
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

    int min_destroyed = N;
    for (int i = 1; i <= N; i++) {
        if (i == c1 || i == c2) continue;

        for (int j = 1; j <= N; j++) {
            graph[i][j] = 0;
            graph[j][i] = 0;
        }

        int components = 0;
        for (int k = 1; k <= N; k++) {
            visited[k] = 0;
        }

        for (int k = 1; k <= N; k++) {
            if (!visited[k]) {
                dfs(k);
                components++;
            }
        }

        min_destroyed = (components > original_components) ? min_destroyed : components;
    }

    printf("%d\n", min_destroyed - original_components + 1);

    return 0;
}