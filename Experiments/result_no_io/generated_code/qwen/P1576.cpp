#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXN 2005
#define MAXM 100005

typedef struct {
    int to;
    double fee;
} Edge;

Edge edges[MAXM];
int parent[MAXN];

double dist[MAXN];

void dijkstra(int n, int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = DBL_MAX;
    }
    dist[start] = 0.0;
    for (int i = 1; i <= n - 1; i++) {
        int u = -1;
        for (int v = 1; v <= n; v++) {
            if (dist[v] != DBL_MAX && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        for (int j = 1; j <= m; j++) {
            if (edges[j].to == u) {
                dist[edges[j].to] = fmin(dist[edges[j].to], dist[u] * (1 - edges[j].fee / 100));
            }
        }
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    parent[find(x)] = find(y);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        double z;
        scanf("%d %d %lf", &x, &y, &z);
        edges[i] = (Edge){y, z};
        edges[m + i] = (Edge){x, z};
    }
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    int A, B;
    scanf("%d %d", &A, &B);

    while (find(A) != find(B)) {
        union_set(A, B);
    }

    dijkstra(n, A);
    printf("%.8f\n", dist[B]);

    return 0;
}