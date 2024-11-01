#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100000

typedef struct {
    double x, y;
} Point;

typedef struct {
    int u, v;
    double weight;
} Edge;

Point points[MAX_N * 2];
Edge edges[MAX_N * MAX_N];
int parent[MAX_N * 2];
int rank[MAX_N * 2];

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->weight > ((Edge*)b)->weight ? 1 : -1;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    double ax, ay, bx, by, cx, cy, dx, dy;
    scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
    scanf("%lf %lf %lf %lf", &cx, &cy, &dx, &dy);
    
    for (int i = 0; i < n; i++) {
        double t;
        scanf("%lf", &t);
        points[i].x = ax * t + bx * (1 - t);
        points[i].y = ay * t + by * (1 - t);
    }
    
    for (int i = 0; i < m; i++) {
        double t;
        scanf("%lf", &t);
        points[n + i].x = cx * t + dx * (1 - t);
        points[n + i].y = cy * t + dy * (1 - t);
    }
    
    int edge_count = 0;
    for (int i = 0; i < n + m; i++) {
        for (int j = i + 1; j < n + m; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].weight = distance(points[i], points[j]);
            edge_count++;
        }
    }
    
    qsort(edges, edge_count, sizeof(Edge), cmp);
    
    for (int i = 0; i < n + m; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    double total_weight = 0;
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (find(u) != find(v)) {
            union_sets(u, v);
            total_weight += edges[i].weight;
        }
    }
    
    printf("%.3f\n", total_weight);
    
    return 0;
}