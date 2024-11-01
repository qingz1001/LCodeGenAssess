#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 200005

typedef struct {
    int u;
    int v;
    int w;
} Edge;

Edge edges[MAXM];
int parent[MAXN];
int rank[MAXN];

// 比较函数，用于排序边
int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

// 并查集查找
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 按边权升序排序
    qsort(edges, m, sizeof(Edge), compare);

    int minDiff = INT_MAX;
    int maxWeight = 0;

    // Kruskal算法求最小生成树
    for (int i = 0; i < m; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            maxWeight = edges[i].w;
        }
    }

    // 再次初始化并查集
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 按边权降序排序
    qsort(edges, m, sizeof(Edge), compare);
    for (int i = m - 1; i >= 0; i--) {
        if (find(edges[i].u) != find(edges[i].v)) {
            unite(edges[i].u, edges[i].v);
            minDiff = edges[i].w - maxWeight;
            break;
        }
    }

    printf("%d\n", minDiff);
    return 0;
}