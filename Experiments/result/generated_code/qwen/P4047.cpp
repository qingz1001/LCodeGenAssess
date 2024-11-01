#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1005

typedef struct {
    int x, y;
} Point;

Point points[MAXN];
int parent[MAXN], rank[MAXN];

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void union_sets(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } else if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    } else {
        parent[pu] = pv;
        rank[pv]++;
    }
}

double kruskal(int n, int k) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    double edges[n * (n - 1) / 2][3];
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[edge_count][0] = distance(points[i], points[j]);
            edges[edge_count][1] = i;
            edges[edge_count][2] = j;
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(double) * 3, [](const void *a, const void *b) {
        return (*(double *)a - *(double *)b);
    });

    int used_edges = 0;
    double min_distance = 0;
    for (int i = 0; i < edge_count && used_edges < n - k; i++) {
        int u = (int)edges[i][1], v = (int)edges[i][2];
        if (find(u) != find(v)) {
            union_sets(u, v);
            used_edges++;
            min_distance = edges[i][0];
        }
    }

    return min_distance;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    printf("%.2f\n", kruskal(n, k));

    return 0;
}