#include <stdio.h>
#include <stdlib.h>

#define MAXN 51

int n, m;
int graph[MAXN][MAXN];
int path[MAXN];
int visited[MAXN];

void dfs(int pos) {
    if (pos == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && graph[path[pos - 1]][i]) {
            path[pos] = i;
            visited[i] = 1;
            dfs(pos + 1);
            visited[i] = 0;
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

    path[0] = 1;
    visited[1] = 1;

    dfs(1);

    return 0;
}