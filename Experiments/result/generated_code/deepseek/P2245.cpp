#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 300005

typedef struct {
    int to, weight, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int parent[MAXN], rank[MAXN];
int max_danger[MAXN][MAXN];

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(int n) {
    qsort(edges, edge_count, sizeof(Edge), cmp);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].to;
        int v = edges[i].weight;
        int w = edges[i].next;
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            union_sets(rootU, rootV);
            max_danger[u][v] = max_danger[v][u] = w;
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        add_edge(a, b, l);
        add_edge(b, a, l);
    }
    kruskal(n);
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (find(a) != find(b)) {
            printf("impossible\n");
        } else {
            printf("%d\n", max_danger[a][b]);
        }
    }
    return 0;
}