#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_P 500

typedef struct {
    int x, y;
} Point;

Point points[MAX_P];
int parent[MAX_P];
int size[MAX_P];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size[x] < size[y]) {
        parent[x] = y;
        size[y] += size[x];
    } else {
        parent[y] = x;
        size[x] += size[y];
    }
}

double dist(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int check(int S, int P, double D) {
    for (int i = 0; i < P; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < P; i++) {
        for (int j = i + 1; j < P; j++) {
            if (dist(points[i], points[j]) <= D) {
                unite(i, j);
            }
        }
    }

    int components = 0;
    for (int i = 0; i < P; i++) {
        if (find(i) == i) components++;
    }

    return components <= S;
}

int main() {
    int S, P;
    scanf("%d %d", &S, &P);

    for (int i = 0; i < P; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    double low = 0, high = 20000, mid;
    while (high - low > 1e-3) {
        mid = (low + high) / 2;
        if (check(S, P, mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }

    printf("%.2f\n", high);

    return 0;
}