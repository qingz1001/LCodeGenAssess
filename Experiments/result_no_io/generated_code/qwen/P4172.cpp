#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 100005
#define INF 1e9

typedef struct {
    int to, cost;
} Edge;

Edge edges[MAXM];
int adj[MAXN][MAXN];
int dist[MAXN];
int parent[MAXN];
int n, m, q;

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != 0 && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
        }
    }
}

int find(int x) {
    if (parent[x] == -1) return x;
    return parent[x] = find(parent[x]);
}

void union_sets(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) {
        parent[px] = py;
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        adj[u][v] = t;
        adj[v][u] = t;
    }
    while (q--) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);
        if (k == 1) {
            dijkstra(u);
            printf("%d\n", dist[v]);
        } else if (k == 2) {
            adj[u][v] = 0;
            adj[v][u] = 0;
            union_sets(u, v);
        }
    }
    return 0;
}