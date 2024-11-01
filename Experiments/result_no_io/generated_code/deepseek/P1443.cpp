#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 400

int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

typedef struct {
    int x, y, steps;
} Point;

int board[MAX][MAX];

void bfs(int n, int m, int start_x, int start_y) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board[i][j] = -1;
        }
    }

    Point queue[MAX * MAX];
    int front = 0, rear = 0;

    queue[rear++] = (Point){start_x, start_y, 0};
    board[start_x][start_y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        int x = current.x;
        int y = current.y;
        int steps = current.steps;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == -1) {
                board[nx][ny] = steps + 1;
                queue[rear++] = (Point){nx, ny, steps + 1};
            }
        }
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    bfs(n, m, x - 1, y - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}