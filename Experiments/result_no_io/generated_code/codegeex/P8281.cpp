#include <stdio.h>
#include <stdlib.h>

int n, m;
int graph[51][51];
int path[51];
int found_paths = 0;

void dfs(int node, int length) {
    if (length == n) {
        if (graph[node][1]) {
            path[length] = 1;
            for (int i = 1; i <= n; i++) {
                printf("%d ", path[i]);
            }
            printf("\n");
            found_paths++;
        }
        return;
    }
    for (int i = 2; i <= n; i++) {
        if (graph[node][i]) {
            path[length] = i;
            dfs(i, length + 1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        graph[u][v] = 1;
    }
    path[0] = 1;
    dfs(1, 1);
    return 0;
}