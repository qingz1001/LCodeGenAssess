#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_M 2500

int n, m;
bool graph[MAX_N + 1][MAX_N + 1];
int path[MAX_N + 1];
bool visited[MAX_N + 1];

void dfs(int depth) {
    if (depth == n && graph[path[n]][1]) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && graph[path[depth]][i]) {
            visited[i] = true;
            path[depth + 1] = i;
            dfs(depth + 1);
            visited[i] = false;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = true;
    }

    path[1] = 1;
    visited[1] = true;
    dfs(1);

    return 0;
}