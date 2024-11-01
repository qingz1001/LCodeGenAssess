#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10005
#define MAXM 20005

typedef struct {
    int a, b, Ti, ti;
} Edge;

int n, k, m;
Edge edges[MAXM];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) parent[px] = py;
}

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->ti - ((Edge *)b)->ti;
}

int kruskal(int max_time) {
    for (int i = 1; i <= n; i++) parent[i] = i;
    int count = 0, max_edge = 0;
    for (int i = 0; i < m; i++) {
        if (edges[i].ti > max_time) continue;
        if (find(edges[i].a) != find(edges[i].b)) {
            union_set(edges[i].a, edges[i].b);
            count++;
            if (edges[i].ti > max_edge) max_edge = edges[i].ti;
        }
    }
    if (count < n - 1) return -1;
    return max_edge;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int left = 0, right = 1e6, ans = INT_MAX;
    while (left <= right) {
        int mid = (left + right) / 2;
        int max_edge = kruskal(mid);
        if (max_edge != -1) {
            ans = max_edge;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}