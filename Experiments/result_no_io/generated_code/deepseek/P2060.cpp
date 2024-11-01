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

int bfs(int dx, int dy) {
    if (dx == 0 && dy == 0) return 0;
    Point queue[10000];
    int front = 0, rear = 0;
    queue[rear++] = (Point){0, 0};
    int dist[100][100];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            dist[i][j] = -1;
    dist[50][50] = 0;
    int moves[8][2] = {{1, 2}, {2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}};
    while (front < rear) {
        Point p = queue[front++];
        for (int i = 0; i < 8; i++) {
            int nx = p.x + moves[i][0];
            int ny = p.y + moves[i][1];
            if (nx == dx && ny == dy) return dist[p.x + 50][p.y + 50] + 1;
            if (nx >= -50 && nx <= 50 && ny >= -50 && ny <= 50 && dist[nx + 50][ny + 50] == -1) {
                dist[nx + 50][ny + 50] = dist[p.x + 50][p.y + 50] + 1;
                queue[rear++] = (Point){nx, ny};
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
    while (dx > 50 || dy > 50) {
        if (dx > dy) {
            dx -= 2;
            dy -= 1;
        } else {
            dx -= 1;
            dy -= 2;
        }
        steps++;
    }
    steps += bfs(dx, dy);
    printf("%d\n", steps);
    return 0;
}