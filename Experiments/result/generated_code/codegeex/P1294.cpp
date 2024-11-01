#include <stdio.h>

#define MAX_N 21
#define MAX_M 51

int n, m;
int graph[MAX_N][MAX_N];
int visited[MAX_N];

int dfs(int current, int length) {
    int max_length = length;
    for (int i = 1; i <= n; i++) {
        if (graph[current][i] > 0 && !visited[i]) {
            visited[i] = 1;
            max_length = (max_length > dfs(i, length + graph[current][i]) ? max_length : dfs(i, length + graph[current][i]));
            visited[i] = 0;
        }
    }
    return max_length;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int max_length = 0;
    for (int i = 1; i <= n; i++) {
        visited[i] = 1;
        max_length = (max_length > dfs(i, 0) ? max_length : dfs(i, 0));
        visited[i] = 0;
    }

    printf("%d\n", max_length);
    return 0;
}