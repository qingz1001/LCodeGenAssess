#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 1000005

typedef struct {
    int u, v, w;
} Edge;

int n, m;
int height[MAXN];
Edge edges[MAXM];
int parent[MAXN];
int rank[MAXN];
int max_scenic_spots;
int min_distance;

void initialize_union_find() {
    for (int i = 1; i <= n; i++) {
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

void process_edges() {
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (height[u] >= height[v]) {
            union_sets(u, v);
        } else if (height[v] >= height[u]) {
            union_sets(v, u);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &height[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    initialize_union_find();
    process_edges();

    int num_components = 0;
    int total_distance = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) {
            num_components++;
        }
    }

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) == find(v)) {
            total_distance += w;
        }
    }

    printf("%d %d\n", num_components, total_distance);
    return 0;
}