#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n;
int graph[MAXN][MAXN];
int degree[MAXN];
int visited[MAXN];
int matched[MAXN];

void dfs(int u, int parent) {
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && v != parent) {
            if (!visited[v]) {
                visited[v] = 1;
                if (matched[v] == -1 || dfs(matched[v], u)) {
                    matched[v] = u;
                    matched[u] = v;
                    return 1;
                }
            } else if (degree[u] > degree[v] && !visited[matched[v]]) {
                visited[v] = 1;
                if (dfs(matched[v], u)) {
                    matched[v] = u;
                    matched[u] = v;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int u, m;
        scanf("%d %d", &u, &m);
        for (int j = 0; j < m; j++) {
            int v;
            scanf("%d", &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
            degree[u]++;
            degree[v]++;
        }
    }

    memset(matched, -1, sizeof(matched));
    int max_match = 0;
    for (int u = 1; u <= n; u++) {
        if (degree[u] % 2 == 1) {
            memset(visited, 0, sizeof(visited));
            if (dfs(u, -1)) {
                max_match++;
            }
        }
    }

    printf("%d\n", max_match / 2);

    return 0;
}