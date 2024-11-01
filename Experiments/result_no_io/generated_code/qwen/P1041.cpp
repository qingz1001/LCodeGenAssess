#include <stdio.h>
#include <stdlib.h>

#define MAXN 305

int n, p;
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int node) {
    visited[node] = 1;
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

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}