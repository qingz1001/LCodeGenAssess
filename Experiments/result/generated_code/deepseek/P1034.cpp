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

int calculate_area(int x1, int y1, int x2, int y2) {
    return (x2 - x1) * (y2 - y1);
}

void dfs(int index, int used_k, int current_area, int x1, int y1, int x2, int y2) {
    if (used_k > k) return;
    if (index == n) {
        if (used_k == k) {
            min_area = (current_area < min_area) ? current_area : min_area;
        }
        return;
    }

    // Include the current point in the current rectangle
    int new_x1 = (points[index].x < x1) ? points[index].x : x1;
    int new_y1 = (points[index].y < y1) ? points[index].y : y1;
    int new_x2 = (points[index].x > x2) ? points[index].x : x2;
    int new_y2 = (points[index].y > y2) ? points[index].y : y2;
    int new_area = calculate_area(new_x1, new_y1, new_x2, new_y2);

    dfs(index + 1, used_k, current_area + new_area, new_x1, new_y1, new_x2, new_y2);

    // Start a new rectangle for the current point
    if (used_k < k) {
        dfs(index + 1, used_k + 1, current_area, points[index].x, points[index].y, points[index].x, points[index].y);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    dfs(0, 1, 0, INT_MAX, INT_MAX, INT_MIN, INT_MIN);

    printf("%d\n", min_area);

    return 0;
}