#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 10001

typedef struct {
    int u;
    int v;
    int w;
} Edge;

int parent[MAXN];
int rank[MAXN];

void init(int n) {
    for (int i = 0; i <= n; i++) {
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

void unite(int x, int y) {
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

int compare(const void *a, const void *b) {
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    return edge1->w - edge2->w;
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    
    Edge edges[MAXM];
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    
    qsort(edges, m, sizeof(Edge), compare);
    
    init(n);
    
    int edges_used = 0;
    int total_weight = 0;
    int components = n;
    
    for (int i = 0; i < m && components > k; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        
        if (find(u) != find(v)) {
            unite(u, v);
            total_weight += w;
            edges_used++;
            components--;
        }
    }
    
    if (components > k) {
        printf("No Answer\n");
    } else {
        printf("%d\n", total_weight);
    }
    
    return 0;
}