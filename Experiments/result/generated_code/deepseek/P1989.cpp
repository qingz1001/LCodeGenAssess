#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], deg[MAXN], vis[MAXN];
int n, m, edge_count;

void add_edge(int u, int v) {
    edges[edge_count].v = v;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
        deg[u]++;
        deg[v]++;
    }

    int ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i != -1; i = edges[i].next) {
            vis[edges[i].v] = u;
        }
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            if (deg[v] > deg[u] || (deg[v] == deg[u] && v > u)) {
                for (int j = head[v]; j != -1; j = edges[j].next) {
                    int w = edges[j].v;
                    if (vis[w] == u) {
                        ans++;
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}