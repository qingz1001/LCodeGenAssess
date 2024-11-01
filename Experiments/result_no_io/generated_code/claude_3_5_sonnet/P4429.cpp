#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 20001

int n, m;
int adj[MAX_N][MAX_N];
int degree[MAX_N];
int match[MAX_N];
bool visited[MAX_N];

bool dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] && !visited[v]) {
            visited[v] = true;
            if (match[v] == 0 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

bool solve() {
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; i++) {
        memset(visited, false, sizeof(visited));
        if (!dfs(i)) {
            return false;
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
            if (degree[i] > n - 2) {
                possible = false;
                break;
            }
        }
        
        if (possible && solve()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}