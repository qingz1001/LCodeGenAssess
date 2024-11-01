#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_M 100005

int n, m;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int color[MAX_N];

int dfs(int v, int c) {
    visited[v] = 1;
    color[v] = c;
    
    for (int i = 1; i <= n; i++) {
        if (graph[v][i]) {
            if (!visited[i]) {
                if (!dfs(i, 1 - c)) return 0;
            } else if (color[i] == color[v]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(color, -1, sizeof(color));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }
    
    int is_bipartite = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 0)) {
                is_bipartite = 0;
                break;
            }
        }
    }
    
    if (!is_bipartite) {
        printf("Impossible\n");
    } else {
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) count++;
        }
        printf("%d\n", count < n - count ? count : n - count);
    }
    
    return 0;
}