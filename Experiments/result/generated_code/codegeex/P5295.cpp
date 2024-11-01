#include <stdio.h>

int T, n, m, u, v, graph[502][502], visited[502];

int dfs(int node) {
    visited[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[node][i]) {
            if (!visited[i]) {
                if (!dfs(i)) return 0;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = 0;
            }
            visited[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        int has_solution = 1;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                if (!dfs(i)) {
                    has_solution = 0;
                    break;
                }
            }
        }
        if (has_solution) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}