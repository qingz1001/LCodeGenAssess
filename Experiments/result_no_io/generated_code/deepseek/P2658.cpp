#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 500

int grid[MAX][MAX];
int waypoints[MAX][MAX];
bool visited[MAX][MAX];
int M, N;

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

bool bfs(int maxDiff) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
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
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (isValid(nx, ny) && !visited[nx][ny] && abs(grid[nx][ny] - grid[current.x][current.y]) <= maxDiff) {
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

    int low = 0, high = INT_MAX, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (bfs(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", low);
    return 0;
}