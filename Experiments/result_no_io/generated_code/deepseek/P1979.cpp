#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 30
#define MAXQ 500

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point p;
    int steps;
} State;

int n, m, q;
int board[MAXN][MAXN];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 1;
}

int bfs(Point start, Point end) {
    bool visited[MAXN][MAXN] = {false};
    State queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (State){start, 0};
    visited[start.x][start.y] = true;

    while (front < rear) {
        State current = queue[front++];
        if (current.p.x == end.x && current.p.y == end.y) {
            return current.steps;
        }
        for (int i = 0; i < 4; i++) {
            int nx = current.p.x + dx[i];
            int ny = current.p.y + dy[i];
            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                queue[rear++] = (State){(Point){nx, ny}, current.steps + 1};
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    for (int i = 0; i < q; i++) {
        int ex, ey, sx, sy, tx, ty;
        scanf("%d %d %d %d %d %d", &ex, &ey, &sx, &sy, &tx, &ty);
        ex--, ey--, sx--, sy--, tx--, ty--;

        if (sx == tx && sy == ty) {
            printf("0\n");
            continue;
        }

        int minSteps = INT_MAX;
        for (int j = 0; j < 4; j++) {
            int nx = sx + dx[j];
            int ny = sy + dy[j];
            if (isValid(nx, ny)) {
                board[sx][sy] = 0;
                board[nx][ny] = 1;
                int steps = bfs((Point){ex, ey}, (Point){nx, ny});
                if (steps != -1) {
                    steps += 1; // Move the target piece to the empty spot
                    steps += bfs((Point){sx, sy}, (Point){tx, ty});
                    if (steps < minSteps) {
                        minSteps = steps;
                    }
                }
                board[sx][sy] = 1;
                board[nx][ny] = 0;
            }
        }

        if (minSteps == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", minSteps);
        }
    }

    return 0;
}