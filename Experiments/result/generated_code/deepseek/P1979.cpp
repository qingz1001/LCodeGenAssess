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
    Point pos;
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
    int visited[MAXN][MAXN] = {0};
    State queue[MAXN * MAXN];
    int front = 0, rear = 0;

    queue[rear++] = (State){start, 0};
    visited[start.x][start.y] = 1;

    while (front < rear) {
        State current = queue[front++];
        if (current.pos.x == end.x && current.pos.y == end.y) {
            return current.steps;
        }
        for (int i = 0; i < 4; i++) {
            int nx = current.pos.x + dx[i];
            int ny = current.pos.y + dy[i];
            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = 1;
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
        int EX, EY, SX, SY, TX, TY;
        scanf("%d %d %d %d %d %d", &EX, &EY, &SX, &SY, &TX, &TY);
        EX--, EY--, SX--, SY--, TX--, TY--;

        if (SX == TX && SY == TY) {
            printf("0\n");
            continue;
        }

        int minSteps = INT_MAX;
        for (int d = 0; d < 4; d++) {
            int nx = SX + dx[d];
            int ny = SY + dy[d];
            if (isValid(nx, ny)) {
                board[SX][SY] = 0;
                board[nx][ny] = 1;
                int steps = bfs((Point){EX, EY}, (Point){nx, ny});
                if (steps != -1) {
                    steps += 1; // Move the target piece to the empty spot
                    steps += bfs((Point){SX, SY}, (Point){TX, TY});
                    if (steps < minSteps) {
                        minSteps = steps;
                    }
                }
                board[SX][SY] = 1;
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