#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 20001

typedef struct {
    int u, v, t, wt;
} Edge;

int n, k, m;
Edge edges[MAXM];
int parent[MAXN];

// 并查集查找
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->t - edgeB->t;
}

int main() {
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d", &edges[i].u, &edges[i].v, &edges[i].wt, &edges[i].t);
    }

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // 按照ti从小到大排序
    qsort(edges, m, sizeof(Edge), cmp);

    int maxTime = 0;
    int count = 0;
    int i = 0;
    while (count < k) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            unionSets(u, v);
            count++;
            maxTime = edges[i].t;
        }
        i++;
    }

    // 继续合并剩余的边，直到所有点连通
    while (i < m) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            unionSets(u, v);
            maxTime = edges[i].t;
        }
        i++;
    }

    printf("%d\n", maxTime);
    return 0;
}