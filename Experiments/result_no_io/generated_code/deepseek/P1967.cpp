#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 50005
#define INF 1000000000

typedef struct {
    int x, y, z;
} Edge;

Edge edges[MAXM];
int parent[MAXN], rank[MAXN];
int n, m, q;

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int cmp(const void *a, const void *b) {
    return ((Edge *)b)->z - ((Edge *)a)->z;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max_weight[MAXN][MAXN];

void kruskal() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    qsort(edges, m, sizeof(Edge), cmp);
    for (int i = 0; i < m; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        int z = edges[i].z;
        if (find(x) != find(y)) {
            union_set(x, y);
            max_weight[x][y] = max_weight[y][x] = z;
        }
    }
}

int dfs(int u, int v, int parent) {
    if (u == v) return INF;
    for (int i = 1; i <= n; i++) {
        if (i != parent && max_weight[u][i] != 0) {
            int res = dfs(i, v, u);
            if (res != -1) return min(max_weight[u][i], res);
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
    }
    kruskal();
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int result = dfs(x, y, -1);
        printf("%d\n", result);
    }
    return 0;
}