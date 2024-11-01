#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];

void dfs(int u) {
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    int components = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }

    if (components == 1) {
        printf("1\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}