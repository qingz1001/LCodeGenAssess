#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

int n;
int adj[MAXN][MAXN], deg[MAXN];
int order[MAXN], cnt;
bool vis[MAXN];

void dfs(int u) {
    vis[u] = true;
    order[cnt++] = u;
    
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (!vis[v]) {
            dfs(v);
        }
    }
    
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        for (int j = 0; j < deg[v]; j++) {
            int w = adj[v][j];
            if (!vis[w]) {
                dfs(w);
            }
        }
    }
}

bool check() {
    for (int i = 1; i < n; i++) {
        bool found = false;
        for (int j = 0; j < deg[order[i-1]]; j++) {
            if (adj[order[i-1]][j] == order[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            bool found2 = false;
            for (int j = 0; j < deg[order[i-1]]; j++) {
                int v = adj[order[i-1]][j];
                for (int k = 0; k < deg[v]; k++) {
                    if (adj[v][k] == order[i]) {
                        found2 = true;
                        break;
                    }
                }
                if (found2) break;
            }
            if (!found2) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }
    
    dfs(1);
    
    if (cnt != n || order[n-1] != n || !check()) {
        printf("BRAK\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d\n", order[i]);
        }
    }
    
    return 0;
}