#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int grid[MAXN][MAXN];
int visited[MAXN][MAXN];
int M, N;

typedef struct {
    int x, y;
} Point;

Point queue[MAXN * MAXN];
int front, rear;

void enqueue(Point p) {
    queue[rear++] = p;
}

Point dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int bfs(Point start) {
    front = rear = 0;
    enqueue(start);
    visited[start.x][start.y] = 1;

    int max_diff = 0;

    while (!isEmpty()) {
        Point current = dequeue();
        int x = current.x;
        int y = current.y;

        int current_height = grid[x][y];

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny]) {
                int height_diff = abs(grid[nx][ny] - current_height);
                max_diff = max(max_diff, height_diff);
                visited[nx][ny] = 1;
                enqueue((Point){nx, ny});
            }
        }
    }

    return max_diff;
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }

    Point start;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int is_landmark;
            scanf("%d", &is_landmark);
            if (is_landmark) {
                start.x = i;
                start.y = j;
                visited[i][j] = 1;
            }
        }
    }

    int difficulty = bfs(start);
    printf("%d\n", difficulty);

    return 0;
}