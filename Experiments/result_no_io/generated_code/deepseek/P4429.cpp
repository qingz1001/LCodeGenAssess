#include <stdio.h>
#include <stdbool.h>

#define MAXN 10005
#define MAXM 20005

int n, m;
int adj[MAXN][MAXN];
int color[MAXN];

bool dfs(int u, int c) {
    color[u] = c;
    for (int v = 1; v <= n; v++) {
        if (adj[u][v]) {
            if (color[v] == c) return false;
            if (color[v] == 0 && !dfs(v, 3 - c)) return false;
        }
    }
    return true;
}

bool isBipartite() {
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                adj[i][j] = 0;
            }
            color[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][v] = adj[v][u] = 1;
        }
        if (isBipartite()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}