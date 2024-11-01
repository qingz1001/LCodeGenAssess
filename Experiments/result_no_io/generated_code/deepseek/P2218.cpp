#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 20000

typedef struct {
    int x, y;
} Point;

Point points[MAXN];
bool covered[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

bool canCover(int n, int L) {
    int minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (int i = 0; i < n; i++) {
        if (!covered[i]) {
            minX = min(minX, points[i].x);
            maxX = max(maxX, points[i].x);
            minY = min(minY, points[i].y);
            maxY = max(maxY, points[i].y);
        }
    }
    return (maxX - minX <= L && maxY - minY <= L);
}

bool check(int n, int L) {
    for (int i = 0; i < n; i++) {
        covered[i] = false;
    }

    // First square
    int minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (int i = 0; i < n; i++) {
        minX = min(minX, points[i].x);
        maxX = max(maxX, points[i].x);
        minY = min(minY, points[i].y);
        maxY = max(maxY, points[i].y);
    }

    for (int i = 0; i < n; i++) {
        if (points[i].x >= minX && points[i].x <= minX + L && points[i].y >= minY && points[i].y <= minY + L) {
            covered[i] = true;
        }
    }

    if (canCover(n, L)) return true;

    // Second square
    minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (int i = 0; i < n; i++) {
        if (!covered[i]) {
            minX = min(minX, points[i].x);
            maxX = max(maxX, points[i].x);
            minY = min(minY, points[i].y);
            maxY = max(maxY, points[i].y);
        }
    }

    for (int i = 0; i < n; i++) {
        if (points[i].x >= minX && points[i].x <= minX + L && points[i].y >= minY && points[i].y <= minY + L) {
            covered[i] = true;
        }
    }

    if (canCover(n, L)) return true;

    // Third square
    minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (int i = 0; i < n; i++) {
        if (!covered[i]) {
            minX = min(minX, points[i].x);
            maxX = max(maxX, points[i].x);
            minY = min(minY, points[i].y);
            maxY = max(maxY, points[i].y);
        }
    }

    for (int i = 0; i < n; i++) {
        if (points[i].x >= minX && points[i].x <= minX + L && points[i].y >= minY && points[i].y <= minY + L) {
            covered[i] = true;
        }
    }

    return canCover(n, L);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    int left = 0, right = 2e9;
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}