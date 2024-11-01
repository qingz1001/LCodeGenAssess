#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50001
#define MAX_M 100001

typedef struct {
    int u, v;
} Edge;

int n, m;
Edge edges[MAX_M];
int parent[MAX_N];
int rank[MAX_N];
int size[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    
    if (root_x == root_y) return;
    
    if (rank[root_x] < rank[root_y]) {
        parent[root_x] = root_y;
        size[root_y] += size[root_x];
    } else if (rank[root_x] > rank[root_y]) {
        parent[root_y] = root_x;
        size[root_x] += size[root_y];
    } else {
        parent[root_y] = root_x;
        size[root_x] += size[root_y];
        rank[root_x]++;
    }
}

int compare(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    return (ea->v > eb->v) - (ea->v < eb->v);
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }
    
    qsort(edges, m, sizeof(Edge), compare);
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
        size[i] = 1;
    }
    
    int max_length = 0;
    
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        int root_u = find(u);
        int root_v = find(v);
        
        if (root_u != root_v) {
            int new_size = size[root_u] + size[root_v];
            union_sets(u, v);
            if (new_size > max_length) {
                max_length = new_size;
            }
        }
    }
    
    printf("%d\n", max_length);
    
    return 0;
}