#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MOD 10000

int n, m, s, t, t0;
int adj[MAXN][MAXN];
int visited[MAXN];

void dfs(int u, int path[], int len, int *count, int *time) {
    if (u == t) {
        (*count)++;
        for (int i = 0; i <= len; i++) {
            (*time) += adj[path[i]][path[i + 1]];
        }
        return;
    }
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] != -1 && !visited[v]) {
            visited[v] = 1;
            path[len + 1] = v;
            dfs(v, path, len + 1, count, time);
            visited[v] = 0;
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &t0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        adj[x][y] = t;
    }

    int path[MAXN], count = 0, time = 0;
    path[0] = s;
    visited[s] = 1;
    dfs(s, path, 0, &count, &time);

    printf("%d\n", (time + count * t0) % MOD);

    return 0;
}