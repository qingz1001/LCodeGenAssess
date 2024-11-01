#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000005

int n, m;
int graph[MAXN][MAXN];
int visited[MAXN];
int group[MAXN];

int dfs(int u, int g) {
    visited[u] = 1;
    group[u] = g;
    int max_depth = 0;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                int depth = dfs(v, g + 1);
                if (depth > max_depth) max_depth = depth;
            } else if (group[v] <= group[u]) {
                return -1;
            }
        }
    }
    return max_depth + 1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
    }
    
    int max_groups = 0;
    int min_groups = n;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            memset(group, 0, sizeof(group));
            int depth = dfs(i, 1);
            if (depth == -1) {
                printf("-1 -1\n");
                return 0;
            }
            if (depth > max_groups) max_groups = depth;
            if (depth < min_groups) min_groups = depth;
        }
    }
    
    if (max_groups < 3) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", max_groups, (min_groups < 3) ? 3 : min_groups);
    }
    
    return 0;
}