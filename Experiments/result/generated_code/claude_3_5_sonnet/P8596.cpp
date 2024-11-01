#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 53280
#define MAX_M 150960

typedef struct {
    int u, v, w;
} Edge;

int n, m, x;
Edge edges[MAX_M];
int parent[MAX_N];
int rank[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx == ry) return;
    if (rank[rx] < rank[ry]) {
        parent[rx] = ry;
    } else {
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) {
            rank[rx]++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int countBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int main() {
    int W;
    scanf("%d", &W);
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < n; i++) {
        int xi, yi;
        scanf("%d %d", &xi, &yi);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalOr = 0;
    int components = n;
    int operations = 0;
    int totalCost = 0;

    printf("%d\n", m);  // 最多m次操作

    for (int i = 0; i < m && components > 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            unite(u, v);
            totalOr |= w;
            components--;
        }

        if (totalOr <= x) {
            int increase = (x + 1) - w;
            if (increase > 0) {
                printf("%d %d %d\n", u, v, increase);
                totalCost += countBits(increase);
                operations++;
            }
        }
    }

    return 0;
}