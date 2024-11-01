#include <stdio.h>
#include <stdlib.h>

#define MAXN 201
#define MAXM 12001

int n, m;
int fa[MAXN];

// 并查集查找
int find(int x) {
    if (fa[x] == x) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

// 并查集合并
void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
    }
}

// Kruskal算法构建最小生成树
int kruskal(int edges[MAXM][3]) {
    int mst_cost = 0;
    for (int i = 0; i < m; i++) {
        if (find(edges[i][0]) != find(edges[i][1])) {
            merge(edges[i][0], edges[i][1]);
            mst_cost += edges[i][2];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (find(i) != find(1)) {
            return -1;
        }
    }
    return mst_cost;
}

int main() {
    int w;
    scanf("%d %d", &n, &w);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int edges[MAXM][3];
    for (int i = 0; i < w; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
        m = i + 1;
        printf("%d\n", kruskal(edges));
    }
    return 0;
}