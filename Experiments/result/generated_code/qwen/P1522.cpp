#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 150

typedef struct {
    int x, y;
} Point;

double distance(Point a, Point b) {
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

double kruskal(int n, Point points[], int adjMatrix[][MAX_N], int *min_diameter) {
    int parent[MAX_N];
    int rank[MAX_N];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    double min_dist = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                double dist = distance(points[i], points[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
    }

    double total_weight = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                double dist = distance(points[i], points[j]);
                if (find(parent, i) != find(parent, j)) {
                    unionSet(parent, rank, i, j);
                    total_weight += dist;
                }
            }
        }
    }

    *min_diameter = (int)(total_weight + 0.5);
    return min_dist;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int adjMatrix[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    int min_diameter;
    double min_dist = kruskal(n, points, adjMatrix, &min_diameter);
    printf("%.6f\n", min_dist);

    return 0;
}