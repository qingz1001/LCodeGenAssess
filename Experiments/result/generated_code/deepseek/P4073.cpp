#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 100005
#define MAXQ 100005

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v, h;
} Edge;

typedef struct {
    double x, y;
} QueryPoint;

Point vertices[MAXN];
Edge edges[MAXM];
QueryPoint queries[MAXQ];
int n, m, q;

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->h - ((Edge *)b)->h;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &vertices[i].x, &vertices[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].h);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%lf %lf %lf %lf", &queries[i].x, &queries[i].y, &queries[i].x, &queries[i].y);
    }

    qsort(edges, m, sizeof(Edge), compareEdges);

    int parent[MAXN], rank[MAXN];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        unionSet(parent, rank, edges[i].u, edges[i].v);
    }

    for (int i = 0; i < q; i++) {
        int u = -1, v = -1;
        for (int j = 0; j < n; j++) {
            if (vertices[j].x == (int)queries[i].x && vertices[j].y == (int)queries[i].y) {
                if (u == -1) u = j;
                else v = j;
            }
        }
        if (u == -1 || v == -1) {
            printf("-1\n");
        } else if (find(parent, u) == find(parent, v)) {
            printf("0\n");
        } else {
            int max_h = INT_MAX;
            for (int j = 0; j < m; j++) {
                if ((find(parent, edges[j].u) == find(parent, u) && find(parent, edges[j].v) == find(parent, v)) ||
                    (find(parent, edges[j].u) == find(parent, v) && find(parent, edges[j].v) == find(parent, u))) {
                    if (edges[j].h < max_h) {
                        max_h = edges[j].h;
                    }
                }
            }
            printf("%d\n", max_h);
        }
    }

    return 0;
}