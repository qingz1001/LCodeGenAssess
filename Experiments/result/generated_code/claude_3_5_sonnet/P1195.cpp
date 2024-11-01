#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 10001
#define INF 0x3f3f3f3f

int parent[MAX_N];
int rank[MAX_N];

typedef struct {
    int x, y, l;
} Edge;

Edge edges[MAX_M];

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->l - ((Edge*)b)->l;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    
    if (root_x == root_y) return;
    
    if (rank[root_x] < rank[root_y]) {
        parent[root_x] = root_y;
    } else {
        parent[root_y] = root_x;
        if (rank[root_x] == rank[root_y]) {
            rank[root_x]++;
        }
    }
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].l);
    }
    
    qsort(edges, m, sizeof(Edge), cmp);
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int components = n;
    int total_cost = 0;
    
    for (int i = 0; i < m && components > k; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        
        if (find(x) != find(y)) {
            unite(x, y);
            total_cost += edges[i].l;
            components--;
        }
    }
    
    if (components == k) {
        printf("%d\n", total_cost);
    } else {
        printf("No Answer\n");
    }
    
    return 0;
}