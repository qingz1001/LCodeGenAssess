#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int visited[MAXN];
int color[MAXN];

void dfs(int u, int c, int graph[MAXN][MAXN], int n) {
    if (visited[u]) return;
    visited[u] = 1;
    color[u] = c;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && color[v] == -1) {
            dfs(v, c ^ 1, graph, n);
        } else if (graph[u][v] && color[v] != -1 && color[v] == color[u]) {
            printf("No\n");
            exit(0);
        }
    }
}

int main() {
    int T, n, m, u, v;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        int graph[MAXN][MAXN];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        for (int i = 1; i <= n; i++) {
            visited[i] = 0;
            color[i] = -1;
        }
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, 0, graph, n);
            }
        }
        printf("Yes\n");
    }
    return 0;
}