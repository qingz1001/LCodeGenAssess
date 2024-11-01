#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10001
#define MAX_M 50001
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], cnt;
int n, m, q;
int fa[MAX_N], rank[MAX_N];
int max_weight[MAX_N][MAX_N];

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        rank[i] = 1;
    }
    memset(max_weight, 0, sizeof(max_weight));
}

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

int find(int x) {
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        fa[x] = y;
    } else {
        fa[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

void kruskal() {
    int edge_count = 0;
    for (int i = 0; i < cnt; i += 2) {
        int u = edges[i ^ 1].to, v = edges[i].to, w = edges[i].weight;
        if (find(u) != find(v)) {
            unite(u, v);
            edge_count++;
            for (int j = 1; j <= n; j++) {
                if (find(j) == find(u)) {
                    for (int k = 1; k <= n; k++) {
                        if (find(k) == find(v)) {
                            max_weight[j][k] = max_weight[k][j] = w;
                        }
                    }
                }
            }
        }
        if (edge_count == n - 1) break;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    init();

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }

    kruskal();

    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (find(x) != find(y)) {
            printf("-1\n");
        } else {
            printf("%d\n", max_weight[x][y]);
        }
    }

    return 0;
}