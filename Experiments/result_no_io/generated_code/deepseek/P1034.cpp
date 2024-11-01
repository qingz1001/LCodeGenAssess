#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50
#define MAXK 4

typedef struct {
    int x, y;
} Point;

int n, k;
Point points[MAXN];
int min_area = INT_MAX;

int abs(int x) {
    return x < 0 ? -x : x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void dfs(int index, int used_k, int area_sum, int xmin, int ymin, int xmax, int ymax) {
    if (used_k > k) return;
    if (index == n) {
        if (used_k == k) {
            min_area = min(min_area, area_sum);
        }
        return;
    }

    // Start a new rectangle
    dfs(index + 1, used_k + 1, area_sum + (xmax - xmin) * (ymax - ymin), points[index].x, points[index].y, points[index].x, points[index].y);

    // Add to the current rectangle
    dfs(index + 1, used_k, area_sum, min(xmin, points[index].x), min(ymin, points[index].y), max(xmax, points[index].x), max(ymax, points[index].y));
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    dfs(1, 1, 0, points[0].x, points[0].y, points[0].x, points[0].y);

    printf("%d\n", min_area);
    return 0;
}