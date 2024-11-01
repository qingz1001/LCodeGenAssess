#include <stdio.h>
#include <stdlib.h>

#define MAX_COORD 10000000
#define MAX_QUEUE_SIZE 1000000

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void enqueue(Queue *queue, Point point) {
    queue->data[queue->rear++] = point;
}

Point dequeue(Queue *queue) {
    return queue->data[queue->front++];
}

int isEmpty(Queue *queue) {
    return queue->front == queue->rear;
}

int abs(int a) {
    return a < 0 ? -a : a;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int horseSteps(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    if (dx > dy) {
        return (dx + dy) / 2 + (dx + dy) % 2;
    } else {
        return (dx + dy) / 2;
    }
}

int main() {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int dist[MAX_COORD + 1][MAX_COORD + 1];
    for (int i = 0; i <= MAX_COORD; i++) {
        for (int j = 0; j <= MAX_COORD; j++) {
            dist[i][j] = -1;
        }
    }

    Queue queue;
    queue.front = queue.rear = 0;
    enqueue(&queue, (Point){x1, y1});
    dist[x1][y1] = 0;

    while (!isEmpty(&queue)) {
        Point current = dequeue(&queue);
        int x = current.x;
        int y = current.y;

        if (x == x2 && y == y2) {
            break;
        }

        int moves[8][2] = {
            {1, 2}, {2, 1}, {1, -2}, {2, -1},
            {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1}
        };

        for (int i = 0; i < 8; i++) {
            int nx = x + moves[i][0];
            int ny = y + moves[i][1];

            if (nx >= 0 && nx <= MAX_COORD && ny >= 0 && ny <= MAX_COORD && dist[nx][ny] == -1) {
                enqueue(&queue, (Point){nx, ny});
                dist[nx][ny] = dist[x][y] + 1;
            }
        }
    }

    printf("%d\n", dist[x2][y2]);
    return 0;
}