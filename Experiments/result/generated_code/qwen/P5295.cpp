#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXM 1001

int visited[MAXN];
int color[MAXN];

void dfs(int u, int c, int edges[][2], int m) {
    if (visited[u]) return;
    visited[u] = 1;
    color[u] = c;
    for (int i = 0; i < m; ++i) {
        if (edges[i][0] == u || edges[i][1] == u) {
            int v = edges[i][0] + edges[i][1] - u;
            dfs(v, c ^ 1, edges, m);
        }
    }
}

int checkBipartite(int n, int m, int edges[][2]) {
    for (int i = 0; i < n; ++i) {
        visited[i] = 0;
        color[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, 0, edges, m);
        }
    }
    for (int i = 0; i < m; ++i) {
        if (color[edges[i][0]] == color[edges[i][1]]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int edges[MAXM][2];
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &edges[i][0], &edges[i][1]);
            edges[i][0]--;
            edges[i][1]--;
        }
        if (checkBipartite(n, m, edges)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}