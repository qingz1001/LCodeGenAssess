#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int min(int a, int b) {
    return a < b ? a : b;
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int bfs(Point start, Point end) {
    if (start.x == end.x && start.y == end.y) return 0;

    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

    Point queue[10000];
    int front = 0, rear = 0;
    queue[rear++] = start;

    int dist[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            dist[i][j] = -1;
        }
    }
    dist[start.x][start.y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 8; i++) {
            Point next = {current.x + dx[i], current.y + dy[i]};
            if (next.x == end.x && next.y == end.y) {
                return dist[current.x][current.y] + 1;
            }
            if (next.x >= 0 && next.x < 100 && next.y >= 0 && next.y < 100 && dist[next.x][next.y] == -1) {
                dist[next.x][next.y] = dist[current.x][current.y] + 1;
                queue[rear++] = next;
            }
        }
    }
    return -1;
}

int main() {
    int xp, yp, xs, ys;
    scanf("%d %d %d %d", &xp, &yp, &xs, &ys);

    int dx = abs(xs - xp);
    int dy = abs(ys - yp);

    int steps = 0;
    while (dx > 40 || dy > 40) {
        if (dx > dy) {
            dx -= 2;
            dy -= 1;
        } else {
            dx -= 1;
            dy -= 2;
        }
        steps++;
    }

    Point start = {(dx + 40) / 2, (dy + 40) / 2};
    Point end = {40, 40};

    steps += bfs(start, end);
    printf("%d\n", steps);

    return 0;
}