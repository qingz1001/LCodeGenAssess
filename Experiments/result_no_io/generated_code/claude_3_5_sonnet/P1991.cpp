#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_P 500

typedef struct {
    int x, y;
} Point;

Point points[MAX_P];
int parent[MAX_P];
double distances[MAX_P][MAX_P];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int compare(const void *a, const void *b) {
    double *da = (double *)a;
    double *db = (double *)b;
    if (*da < *db) return -1;
    if (*da > *db) return 1;
    return 0;
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    for (int i = 0; i < P; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        parent[i] = i;
    }

    double all_distances[MAX_P * (MAX_P - 1) / 2];
    int count = 0;

    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            distances[i][j] = distances[j][i] = distance(points[i], points[j]);
            all_distances[count++] = distances[i][j];
        }
    }

    qsort(all_distances, count, sizeof(double), compare);

    int components = P;
    double result = 0;

    for (int i = 0; i < count && components > S; i++) {
        double d = all_distances[i];
        for (int j = 0; j < P; j++) {
            for (int k = j + 1; k < P; k++) {
                if (distances[j][k] <= d && find(j) != find(k)) {
                    unite(j, k);
                    components--;
                    if (components == S) {
                        result = d;
                        break;
                    }
                }
            }
            if (components == S) break;
        }
    }

    printf("%.2f\n", result);

    return 0;
}