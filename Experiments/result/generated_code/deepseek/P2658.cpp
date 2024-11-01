#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 500

int M, N;
int grid[MAX][MAX];
int waypoints[MAX][MAX];
bool visited[MAX][MAX];

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point points[MAX * MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, Point p) {
    q->points[q->rear++] = p;
}

Point dequeue(Queue *q) {
    return q->points[q->front++];
}

bool isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

bool bfs(int D) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    Queue q;
    initQueue(&q);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (waypoints[i][j]) {
                enqueue(&q, (Point){i, j});
                visited[i][j] = true;
            } else {
                visited[i][j] = false;
            }
        }
    }

    while (!isEmpty(&q)) {
        Point current = dequeue(&q);
        int x = current.x;
        int y = current.y;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny] && abs(grid[nx][ny] - grid[x][y]) <= D) {
                visited[nx][ny] = true;
                enqueue(&q, (Point){nx, ny});
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (waypoints[i][j] && !visited[i][j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    scanf("%d %d", &M, &N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &waypoints[i][j]);
        }
    }

    int left = 0, right = 1e9;
    int result = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (bfs(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", result);

    return 0;
}