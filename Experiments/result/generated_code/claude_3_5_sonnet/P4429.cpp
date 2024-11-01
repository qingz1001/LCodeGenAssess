#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

int adj[MAX_N][MAX_N];
int degree[MAX_N];
bool visited[MAX_N];
int color[MAX_N];
int n, m;

bool dfs(int v, int c) {
    visited[v] = true;
    color[v] = c;
    
    for (int i = 1; i <= n; i++) {
        if (adj[v][i]) {
            if (visited[i]) {
                if (color[i] == c) return false;
            } else {
                if (!dfs(i, 1 - c)) return false;
            }
        }
    }
    
    return true;
}

bool is_bipartite() {
    memset(visited, 0, sizeof(visited));
    memset(color, -1, sizeof(color));
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 0)) return false;
        }
    }
    
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &n, &m);
        
        memset(adj, 0, sizeof(adj));
        memset(degree, 0, sizeof(degree));
        
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][v] = adj[v][u] = 1;
            degree[u]++;
            degree[v]++;
        }
        
        bool possible = true;
        for (int i = 1; i <= n; i++) {
            if (degree[i] > 2) {
                possible = false;
                break;
            }
        }
        
        if (possible && is_bipartite()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}