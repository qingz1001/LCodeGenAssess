#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1005

typedef struct {
    int x, y;
} Point;

Point points[MAXN];
int parent[MAXN];
double dist[MAXN][MAXN];

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
    int pu = find(u);
    int pv = find(v);
    if (pu != pv) {
        parent[pu] = pv;
    }
}

double kruskal(int n, int k) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    double min_dist = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = distance(points[i], points[j]);
        }
    }

    while (k > 1) {
        double min_val = 1e9;
        int u = -1, v = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist[i][j] < min_val && find(i) != find(j)) {
                    min_val = dist[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        union_sets(u, v);
        k--;
    }

    double max_dist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (find(i) != find(j)) {
                max_dist = fmax(max_dist, dist[i][j]);
            }
        }
    }

    return max_dist;
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