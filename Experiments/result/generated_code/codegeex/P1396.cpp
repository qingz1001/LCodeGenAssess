#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10001
#define MAXM 20001

struct Edge {
    int to, weight;
};

int n, m, s, t;
struct Edge graph[MAXM];
int parent[MAXN];
int rank[MAXN];

// 初始化并查集
void init_union_find(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// 查找并查集的根节点
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并两个集合
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

// 比较函数，用于排序边
int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->weight - edgeB->weight;
}

// Kruskal算法求最小生成树
int kruskal() {
    int maxWeight = 0;
    int edgesUsed = 0;
    init_union_find(n);
    qsort(graph, m, sizeof(struct Edge), compare);

    for (int i = 0; i < m && edgesUsed < n - 1; i++) {
        int u = graph[i].to;
        int v = graph[i].weight;
        if (find(u) != find(v)) {
            union_sets(u, v);
            maxWeight = v;
            edgesUsed++;
        }
    }
    return maxWeight;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &graph[i].to, &graph[i + m].to, &graph[i].weight);
        graph[i + m].to = graph[i].to;
        graph[i + m].weight = graph[i].weight;
        graph[i].to = i;
        graph[i + m].to = i + m;
    }
    int result = kruskal();
    printf("%d\n", result);
    return 0;
}