#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 300005

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    Edge edges[MAXM];
    int head[MAXN];
    int next[MAXM];
    int edge_count;
} Graph;

Graph graph;
int parent[MAXN];
int rank[MAXN];

void init_graph(int n) {
    graph.edge_count = 0;
    for (int i = 1; i <= n; i++) {
        graph.head[i] = -1;
    }
}

void add_edge(int u, int v, int w) {
    graph.edges[graph.edge_count].to = v;
    graph.edges[graph.edge_count].weight = w;
    graph.next[graph.edge_count] = graph.head[u];
    graph.head[u] = graph.edge_count++;
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

int min_danger[MAXN][MAXN];

void kruskal(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            min_danger[u][v] = INT_MAX;
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int i = graph.head[u]; i != -1; i = graph.next[i]) {
            int v = graph.edges[i].to;
            int w = graph.edges[i].weight;
            int rootU = find(u);
            int rootV = find(v);
            if (rootU != rootV) {
                union_sets(rootU, rootV);
                min_danger[rootU][rootV] = min_danger[rootV][rootU] = w;
            } else {
                min_danger[rootU][rootV] = min_danger[rootV][rootU] = w;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    init_graph(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    kruskal(n);

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) {
            printf("%d\n", min_danger[rootU][rootV]);
        } else {
            printf("impossible\n");
        }
    }

    return 0;
}