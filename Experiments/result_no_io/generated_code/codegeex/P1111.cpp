#include <stdio.h>
#include <stdlib.h>

// 定义最大村庄数
#define MAX_VILLAGES 1001

// 定义边结构体
typedef struct {
    int u; // 起点
    int v; // 终点
    int t; // 修复完成时间
} Edge;

// 比较函数，用于按修复完成时间排序边
int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->t - edgeB->t;
}

// 并查集查找函数
int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    else
        return find(parent, parent[i]);
}

// 并查集合并函数
void unionSets(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Edge edges[M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].t);
    }

    // 按修复完成时间排序边
    qsort(edges, M, sizeof(Edge), compare);

    // 初始化并查集
    int parent[N];
    for (int i = 0; i < N; i++) {
        parent[i] = -1;
    }

    int components = N; // 初始组件数
    int earliest_time = -1; // 最早通车时间

    for (int i = 0; i < M; i++) {
        int x = edges[i].u;
        int y = edges[i].v;
        int t = edges[i].t;

        // 如果两个村庄不在同一个组件中，合并它们
        if (find(parent, x) != find(parent, y)) {
            unionSets(parent, x, y);
            components--;

            // 如果所有村庄都在同一个组件中，记录时间
            if (components == 1) {
                earliest_time = t;
                break;
            }
        }
    }

    // 如果所有村庄都在同一个组件中，输出最早通车时间，否则输出-1
    printf("%d\n", earliest_time);

    return 0;
}