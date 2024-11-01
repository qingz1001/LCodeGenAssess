#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_M 500
#define MAX_AB 100000

int n, m, a, b;
int grid[MAX_N][MAX_M];
int queue[MAX_AB * 2][2];
int front = 0, rear = 0;

void bfs() {
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == -1) {
                grid[nx][ny] = grid[x][y] + 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);

    memset(grid, -1, sizeof(grid));

    for (int i = 0; i < a; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        grid[x][y] = 0;
        queue[rear][0] = x;
        queue[rear][1] = y;
        rear++;
    }

    bfs();

    for (int i = 0; i < b; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        printf("%d\n", grid[x][y]);
    }

    return 0;
}