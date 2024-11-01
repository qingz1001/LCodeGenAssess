#include <stdio.h>
#include <stdlib.h>

// 定义最大景点数
#define MAX_N 20

// 定义图的边结构
typedef struct {
    int u;  // 起点
    int v;  // 终点
    int w;  // 权重（路程）
} Edge;

// 比较函数，用于排序边
int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

// 找到某个节点的根节点
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    else
        return find(parent, parent[i]);
}

// 合并两个集合
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
}

// Kruskal算法求最大生成树
int kruskal(Edge edges[], int n, int m) {
    int parent[MAX_N];
    int rank[MAX_N];

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        rank[i] = 0;
    }

    qsort(edges, m, sizeof(Edge), compare);

    int maxWeight = 0;
    int edgesUsed = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(parent, u) != find(parent, v)) {
            unionSets(parent, rank, u, v);
            maxWeight += edges[i].w;
            edgesUsed++;
            if (edgesUsed == n - 1)
                break;
        }
    }

    return maxWeight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge edges[m];

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].u--;  // 转换为0索引
        edges[i].v--;  // 转换为0索引
    }

    int maxWeight = kruskal(edges, n, m);
    printf("%d\n", maxWeight);

    return 0;
}