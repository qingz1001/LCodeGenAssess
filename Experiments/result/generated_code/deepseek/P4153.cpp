#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150000
#define MAXM 300000
#define MAXK 500000

typedef struct {
    int x, y, z;
} Edge;

Edge edges[MAXM];
int n, m, s, t, k;
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) parent[rootX] = rootY;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->z - ((Edge *)b)->z;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].z);
    }

    qsort(edges, m, sizeof(Edge), compare);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int count = 0;
    int total_weight = 0;
    int results[MAXK];

    for (int i = 0; i < m; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        int z = edges[i].z;

        if (find(x) != find(y)) {
            union_set(x, y);
            results[count++] = z;
            total_weight += z;
            if (count == k) break;
        }
    }

    if (count < k) {
        for (int i = 0; i < count; i++) {
            printf("%d\n", results[i]);
        }
        printf("-1\n");
    } else {
        for (int i = 0; i < k; i++) {
            printf("%d\n", results[i]);
        }
    }

    return 0;
}