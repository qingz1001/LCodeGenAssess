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

bool canCoverAll(int n, int L) {
    int minX = points[0].x, maxX = points[0].x;
    int minY = points[0].y, maxY = points[0].y;

    for (int i = 1; i < n; i++) {
        minX = min(minX, points[i].x);
        maxX = max(maxX, points[i].x);
        minY = min(minY, points[i].y);
        maxY = max(maxY, points[i].y);
    }

    int width = maxX - minX;
    int height = maxY - minY;

    if (width <= L && height <= L) return true;
    if (width > L && height > L) return false;

    int coverX = (width > L) ? (width + 1) / 2 : L;
    int coverY = (height > L) ? (height + 1) / 2 : L;

    for (int i = 0; i < n; i++) {
        if (points[i].x >= minX && points[i].x <= minX + coverX &&
            points[i].y >= minY && points[i].y <= minY + coverY) {
            covered[i] = true;
        } else {
            covered[i] = false;
        }
    }

    int newMinX = 1e9, newMaxX = -1e9;
    int newMinY = 1e9, newMaxY = -1e9;

    for (int i = 0; i < n; i++) {
        if (!covered[i]) {
            newMinX = min(newMinX, points[i].x);
            newMaxX = max(newMaxX, points[i].x);
            newMinY = min(newMinY, points[i].y);
            newMaxY = max(newMaxY, points[i].y);
        }
    }

    int newWidth = newMaxX - newMinX;
    int newHeight = newMaxY - newMinY;

    return newWidth <= L && newHeight <= L;
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
        if (canCoverAll(n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);

    return 0;
}