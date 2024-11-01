#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 400
#define MAX_M 400

int n, m, x, y;
int board[MAX_N][MAX_M];
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

typedef struct {
    int x, y;
} Point;

Point queue[MAX_N * MAX_M];
int front, rear;

void bfs(int startX, int startY) {
    memset(board, -1, sizeof(board));
    front = rear = 0;

    queue[rear++] = (Point){startX, startY};
    board[startX][startY] = 0;

    while (front < rear) {
        Point current = queue[front++];

        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == -1) {
                board[nx][ny] = board[current.x][current.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &x, &y);

    bfs(x - 1, y - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%-5d", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}