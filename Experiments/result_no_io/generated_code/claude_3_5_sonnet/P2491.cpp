#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define INF 0x3f3f3f3f

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt;
int n, s;
int dist[MAXN], max_dist[MAXN], parent[MAXN];
int diameter, diameter_end;

void add_edge(int u, int v, int w) {
    edges[++cnt] = (Edge){v, head[u], w};
    head[u] = cnt;
    edges[++cnt] = (Edge){u, head[v], w};
    head[v] = cnt;
}

void dfs(int u, int p, int d) {
    dist[u] = d;
    parent[u] = p;
    if (d > dist[diameter_end]) {
        diameter_end = u;
    }
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + edges[i].weight);
        }
    }
}

void get_max_dist(int u, int p, int d) {
    max_dist[u] = d;
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            get_max_dist(v, u, d + edges[i].weight);
        }
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    dfs(1, 0, 0);
    int end1 = diameter_end;
    memset(dist, 0, sizeof(dist));
    diameter_end = 0;
    dfs(end1, 0, 0);
    int end2 = diameter_end;
    diameter = dist[end2];

    if (diameter <= s) {
        printf("0\n");
        return 0;
    }

    int u = end2;
    int path_len = 0;
    while (path_len + dist[parent[u]] <= s) {
        path_len += dist[u] - dist[parent[u]];
        u = parent[u];
    }

    get_max_dist(u, 0, 0);
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = result > max_dist[i] ? result : max_dist[i];
    }

    printf("%d\n", result);
    return 0;
}