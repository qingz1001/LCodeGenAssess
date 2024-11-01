#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 100
#define INF INT_MAX

int N, M;
int grid[MAXN][MAXM];
int dist[MAXN][MAXM];

typedef struct {
    int x, y, d;
} State;

typedef struct {
    State data[MAXN * MAXM * 8];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, State s) {
    q->data[q->rear++] = s;
}

State dequeue(Queue *q) {
    return q->data[q->front++];
}

int isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int bfs() {
    Queue q;
    initQueue(&q);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = 0;
    enqueue(&q, (State){0, 0, -1});

    while (!isEmpty(&q)) {
        State cur = dequeue(&q);
        int x = cur.x, y = cur.y, d = cur.d;

        for (int i = 0; i < 8; i++) {
            if (i == d) continue;
            int nx = x + dx[i] * grid[x][y];
            int ny = y + dy[i] * grid[x][y];
            if (isValid(nx, ny) && dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                enqueue(&q, (State){nx, ny, i});
            }
        }
    }

    return dist[N-1][M-1] == INF ? -1 : dist[N-1][M-1];
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int result = bfs();
    if (result == -1) {
        printf("NEVER\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}