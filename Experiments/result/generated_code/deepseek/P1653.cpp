#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int W, L;
int grid[MAX][MAX];
int visited[MAX][MAX];

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point data[MAX * MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, Point p) {
    q->data[q->rear++] = p;
}

Point dequeue(Queue *q) {
    return q->data[q->front++];
}

void bfs(int x, int y) {
    Queue q;
    initQueue(&q);
    Point start = {x, y};
    enqueue(&q, start);
    visited[x][y] = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!isEmpty(&q)) {
        Point current = dequeue(&q);
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < L && ny >= 0 && ny < W && !visited[nx][ny] && grid[nx][ny] <= grid[current.x][current.y]) {
                visited[nx][ny] = 1;
                Point next = {nx, ny};
                enqueue(&q, next);
            }
        }
    }
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int components = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            if (!visited[i][j]) {
                bfs(i, j);
                components++;
            }
        }
    }

    int minCars = components - 1;
    printf("%d\n", minCars);

    return 0;
}