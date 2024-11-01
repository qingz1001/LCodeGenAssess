#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];
int count[MAXN];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = 1;
    count[node]++;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", count[i]);
    }
    printf("\n");

    return 0;
}