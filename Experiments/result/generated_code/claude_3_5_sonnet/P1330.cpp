#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10001
#define MAX_M 100001

int n, m;
int graph[MAX_N][MAX_N];
bool visited[MAX_N];
int color[MAX_N];

bool dfs(int v, int c) {
    visited[v] = true;
    color[v] = c;
    
    for (int i = 1; i <= n; i++) {
        if (graph[v][i]) {
            if (!visited[i]) {
                if (!dfs(i, !c)) return false;
            } else if (color[i] == c) {
                return false;
            }
        }
    }
    
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }
    
    bool isBipartite = true;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 0)) {
                isBipartite = false;
                break;
            }
        }
    }
    
    if (!isBipartite) {
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