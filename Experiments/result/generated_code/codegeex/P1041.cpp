#include <stdio.h>

int n, p;
int graph[301][301];
int visited[301];
int count;

void dfs(int node) {
    visited[node] = 1;
    count++;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < p; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    dfs(1);

    printf("%d\n", n - count);

    return 0;
}