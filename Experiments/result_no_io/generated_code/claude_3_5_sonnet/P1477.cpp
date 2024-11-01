#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];
int color[MAXN];

int dfs(int v, int c) {
    visited[v] = 1;
    color[v] = c;
    for (int i = 1; i <= n; i++) {
        if (graph[v][i]) {
            if (visited[i]) {
                if (color[i] == c) return 0;
            } else {
                if (!dfs(i, 3 - c)) return 0;
            }
        }
    }
    return 1;
}

int is_bipartite() {
    memset(visited, 0, sizeof(visited));
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 1)) return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
    }
    
    int max_classes = n;
    int min_classes = 2;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (graph[i][j] && graph[j][i]) {
                printf("-1 -1\n");
                return 0;
            }
        }
    }
    
    if (!is_bipartite()) {
        min_classes = 3;
    }
    
    if (min_classes < 3) min_classes = 3;
    
    printf("%d %d\n", max_classes, min_classes);
    
    return 0;
}