#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50

typedef struct {
    long long x, y;
} Point;

Point points[MAX_N];
int parent[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        parent[rx] = ry;
    }
}

int is_connected(int n) {
    int root = find(0);
    for (int i = 1; i < n; i++) {
        if (find(i) != root) {
            return 0;
        }
    }
    return 1;
}

int are_points_connected(Point a, Point b, long long time) {
    long long dx = llabs(a.x - b.x);
    long long dy = llabs(a.y - b.y);
    return dx <= 2 * time && dy <= 2 * time;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
        parent[i] = i;
    }

    long long left = 0, right = 2000000000;
    while (left < right) {
        long long mid = (left + right) / 2;

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (are_points_connected(points[i], points[j], mid)) {
                    unite(i, j);
                }
            }
        }

        if (is_connected(n)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);
    return 0;
}