#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
#define MAX_M 50

int n, m;
int graph[MAX_N][MAX_N];

void dfs(int start, int end, int visited[], int path_length, int *max_path) {
    if (path_length > *max_path) {
        *max_path = path_length;
    }
    for (int i = 0; i < n; i++) {
        if (graph[start][i] && !visited[i]) {
            visited[i] = 1;
            dfs(i, end, visited, path_length + graph[start][i], max_path);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u-1][v-1] = w;
        graph[v-1][u-1] = w;
    }

    int max_path = 0;
    for (int i = 0; i < n; i++) {
        int visited[MAX_N] = {0};
        visited[i] = 1;
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) {
                visited[j] = 1;
                dfs(j, i, visited, graph[i][j], &max_path);
                visited[j] = 0;
            }
        }
    }

    printf("%d\n", max_path);
    return 0;
}