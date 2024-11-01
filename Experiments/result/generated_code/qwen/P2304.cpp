#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

int n;
Point trees[MAXN];
int visited[MAXN];

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int dfs(int x, int y, int direction) {
    if (visited[x * 10000 + y]) return 0;
    visited[x * 10000 + y] = 1;
    int max_stops = 1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            if (abs(dx) != abs(dy)) continue;
            int nx = x + dx, ny = y + dy;
            int min_dist = INF;
            for (int i = 1; i <= n; i++) {
                if (!visited[trees[i].x * 10000 + trees[i].y]) {
                    int d = dist(nx, ny, trees[i].x, trees[i].y);
                    if (d < min_dist) min_dist = d;
                }
            }
            if (min_dist != INF) {
                max_stops += dfs(trees[min_dist / 10000].x, trees[min_dist % 10000].y, direction);
            }
        }
    }
    return max_stops;
}

void find_optimal_route() {
    int max_stops = 0;
    int best_x = 0, best_y = 0;
    for (int i = 1; i <= n; i++) {
        int stops = dfs(0, 0, 0);
        if (stops > max_stops) {
            max_stops = stops;
            best_x = trees[i].x;
            best_y = trees[i].y;
        }
    }
    printf("%d\n", max_stops);
    printf("1 %d\n", i);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }
    find_optimal_route();
    return 0;
}