#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    double w;
} Edge;

Edge edges[100001];
double a[1001];
int parent[1001];

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

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w > edgeB->w ? -1 : 1;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        a[i] = 0.0;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d %lf", &edges[i].x, &edges[i].y, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), compare);

    for (int i = 0; i < M; i++) {
        int x = edges[i].x;
        int y = edges[i].y;
        double w = edges[i].w;
        if (find(x) != find(y)) {
            union_sets(x, y);
            a[x] = (w - a[x] - a[y]) / 2.0;
            a[y] = w - a[x];
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%.2lf\n", a[i]);
    }

    return 0;
}