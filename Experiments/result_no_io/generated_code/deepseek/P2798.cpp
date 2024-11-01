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
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int compare_edges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->ti - edgeB->ti;
}

int kruskal(int max_time) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int count = 0;
    int self_thought_count = 0;

    for (int i = 0; i < m; i++) {
        if (edges[i].ti <= max_time) {
            if (find(edges[i].a) != find(edges[i].b)) {
                union_sets(edges[i].a, edges[i].b);
                count++;
                if (edges[i].ti < edges[i].Ti) {
                    self_thought_count++;
                }
            }
        }
    }

    if (count < n - 1 || self_thought_count < k) {
        return 0;
    }

    return 1;
}

int main() {
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &edges[i].a, &edges[i].b, &edges[i].Ti, &edges[i].ti);
    }

    qsort(edges, m, sizeof(Edge), compare_edges);

    int left = 0, right = INT_MAX;
    int result = INT_MAX;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (kruskal(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", result);

    return 0;
}