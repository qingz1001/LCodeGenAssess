#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 150
#define INF 1e9

typedef struct {
    int x, y;
} Point;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

double kruskal(int n, Point points[], int graph[MAX_N][MAX_N], int *min_diameter) {
    int parent[n];
    int rank[n];

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    double min_dist = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] == 1) {
                double d = dist(points[i], points[j]);
                if (d < min_dist) {
                    min_dist = d;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] == 1) {
                double d = dist(points[i], points[j]);
                if (d != min_dist) {
                    int u = find(parent, i);
                    int v = find(parent, j);
                    if (u != v) {
                        unionSet(parent, rank, u, v);
                        *min_diameter = fmax(*min_diameter, d);
                    }
                }
            }
        }
    }

    return min_dist;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAX_N];
    int graph[MAX_N][MAX_N];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int min_diameter = 0;
    double result = kruskal(n, points, graph, &min_diameter);

    printf("%.6f\n", result);

    return 0;
}