#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 50

typedef struct {
    int x, y;
} Point;

bool inRange(int x, int y, int t) {
    return (x >= -t && x <= t && y >= -t && y <= t);
}

bool connected(Point a, Point b, int t) {
    for (int dx = -t; dx <= t; ++dx) {
        for (int dy = -t; dy <= t; ++dy) {
            if (inRange(a.x + dx, a.y + dy, t) && inRange(b.x - dx, b.y - dy, t)) {
                return true;
            }
        }
    }
    return false;
}

bool isConnected(Point points[], int n, int t) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!connected(points[i], points[j], t)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int t = 0;
    while (!isConnected(points, n, t)) {
        t++;
    }

    printf("%d\n", t);

    return 0;
}