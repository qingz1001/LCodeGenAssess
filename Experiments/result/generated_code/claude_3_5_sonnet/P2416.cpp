#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300005
#define MAX_M 300005

typedef struct Edge {
    int to, next, has_puff;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], edge_cnt;
int vis[MAX_N];
int has_puff;

void add_edge(int u, int v, int z) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].has_puff = z;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

void dfs(int u, int t) {
    if (u == t) {
        has_puff = 1;
        return;
    }

    vis[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (!vis[v]) {
            if (edges[i].has_puff) has_puff = 1;
            dfs(v, t);
            if (has_puff) return;
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }

    scanf("%d", &q);

    while (q--) {
        int s, t;
        scanf("%d %d", &s, &t);

        memset(vis, 0, sizeof(vis));
        has_puff = 0;
        dfs(s, t);

        printf("%s\n", has_puff ? "YES" : "NO");
    }

    return 0;
}