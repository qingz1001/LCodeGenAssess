#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define INF 1000000000

typedef struct {
    int x, y;
} Point;

int n;
Point points[MAXN];
int grid[2 * MAXN][2 * MAXN];

void initialize() {
    for (int i = 0; i < 2 * MAXN; i++) {
        for (int j = 0; j < 2 * MAXN; j++) {
            grid[i][j] = -1;
        }
    }
}

void mark(int x, int y, int t) {
    if (x >= 0 && x < 2 * MAXN && y >= 0 && y < 2 * MAXN) {
        grid[x][y] = t;
    }
}

int bfs() {
    int queue[MAXN * MAXN];
    int front = 0, rear = 0;
    int visited[MAXN * MAXN] = {0};

    for (int i = 0; i < n; i++) {
        int x = points[i].x + MAXN;
        int y = points[i].y + MAXN;
        queue[rear++] = x * 2 * MAXN + y;
        visited[x * 2 * MAXN + y] = 1;
        mark(x, y, 0);
    }

    while (front != rear) {
        int u = queue[front++];
        int x = u / (2 * MAXN);
        int y = u % (2 * MAXN);

        if (grid[x - 1][y] == -1) {
            grid[x - 1][y] = grid[x][y] + 1;
            queue[rear++] = (x - 1) * 2 * MAXN + y;
        }
        if (grid[x + 1][y] == -1) {
            grid[x + 1][y] = grid[x][y] + 1;
            queue[rear++] = (x + 1) * 2 * MAXN + y;
        }
        if (grid[x][y - 1] == -1) {
            grid[x][y - 1] = grid[x][y] + 1;
            queue[rear++] = x * 2 * MAXN + (y - 1);
        }
        if (grid[x][y + 1] == -1) {
            grid[x][y + 1] = grid[x][y] + 1;
            queue[rear++] = x * 2 * MAXN + (y + 1);
        }
    }

    int max_time = 0;
    for (int i = 0; i < 2 * MAXN; i++) {
        for (int j = 0; j < 2 * MAXN; j++) {
            if (grid[i][j] != -1 && grid[i][j] > max_time) {
                max_time = grid[i][j];
            }
        }
    }

    return max_time;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    initialize();
    int result = bfs();

    printf("%d\n", result);

    return 0;
}