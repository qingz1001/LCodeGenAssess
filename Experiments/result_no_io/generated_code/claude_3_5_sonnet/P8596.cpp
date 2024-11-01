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
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int popcount(unsigned int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int main() {
    int W;
    scanf("%d", &W);
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int total_or = 0;
    int components = n;
    int operations = 0;

    printf("0\n");  // No operations needed initially

    for (int i = 0; i < m && components > 1; i++) {
        int u = edges[i].u - 1;
        int v = edges[i].v - 1;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            unite(u, v);
            total_or |= w;
            components--;
        }
    }

    if (total_or <= x) {
        int increase = x - total_or + 1;
        int cost = popcount(increase);
        operations++;
        printf("%d\n", operations);
        printf("%d %d %d\n", edges[0].u, edges[0].v, increase);
    }

    return 0;
}