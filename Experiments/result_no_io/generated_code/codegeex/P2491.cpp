#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXM 300005

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAXM];
int parent[MAXN], rank[MAXN];
int dist[MAXN];
int n, m, s;

void init_union_find(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
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

void kruskal() {
    init_union_find(n);
    int edges_used = 0;
    for (int i = 0; i < m && edges_used < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            union_sets(u, v);
            edges_used++;
        }
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    m = n - 1;

    kruskal();

    int result = INT_MAX;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (w <= s) {
            int max_dist = 0;
            for (int j = 0; j < n; j++) {
                dist[j] = INT_MAX;
            }
            dist[u] = 0;
            dist[v] = 0;
            for (int j = 0; j < m; j++) {
                if (j != i && find(edges[j].u) != find(edges[j].v)) {
                    union_sets(edges[j].u, edges[j].v);
                }
            }
            for (int j = 0; j < m; j++) {
                if (j != i) {
                    int u = edges[j].u;
                    int v = edges[j].v;
                    int w = edges[j].w;
                    if (find(u) == find(v)) {
                        int min_dist = dist[u] < dist[v] ? dist[u] : dist[v];
                        dist[u] = dist[v] = min_dist + w;
                    }
                }
            }
            for (int j = 0; j < n; j++) {
                max_dist = max_dist < dist[j] ? dist[j] : max_dist;
            }
            result = result < max_dist ? result : max_dist;
        }
    }

    printf("%d\n", result);
    return 0;
}