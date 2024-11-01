#include <stdio.h>
#include <stdlib.h>

#define MAXN 705

int n;
int graph[MAXN][MAXN];
int visited[MAXN];

long long dfs(int node) {
    if (visited[node]) return 0;
    visited[node] = 1;
    int size = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i]) {
            size += dfs(i);
        }
    }
    return size;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    long long max_product = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            long long size = dfs(i);
            max_product *= size;
        }
    }

    printf("%lld\n", max_product);

    return 0;
}