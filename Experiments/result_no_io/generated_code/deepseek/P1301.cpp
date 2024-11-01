#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 100
#define INF INT_MAX

int N, M;
int grid[MAXN][MAXM];
int dist[MAXN][MAXM];
int visited[MAXN][MAXM];

typedef struct {
    int x, y, steps;
} Node;

Node queue[MAXN * MAXM];
int front = 0, rear = 0;

void enqueue(int x, int y, int steps) {
    queue[rear].x = x;
    queue[rear].y = y;
    queue[rear].steps = steps;
    rear++;
}

Node dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int isValid(int x, int y, int prev_x, int prev_y) {
    if (x < 0 || x >= N || y < 0 || y >= M) return 0;
    if (visited[x][y]) return 0;
    if (x == prev_x && y == prev_y) return 0;
    return 1;
}

int minSteps() {
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
            visited[i][j] = 0;
        }
    }

    dist[0][0] = 0;
    enqueue(0, 0, 0);

    while (!isEmpty()) {
        Node curr = dequeue();
        int x = curr.x;
        int y = curr.y;
        int steps = curr.steps;

        if (x == N - 1 && y == M - 1) return steps;

        visited[x][y] = 1;

        for (int d = 0; d < 8; d++) {
            int nx = x + dx[d] * grid[x][y];
            int ny = y + dy[d] * grid[x][y];

            if (isValid(nx, ny, x, y) && steps + 1 < dist[nx][ny]) {
                dist[nx][ny] = steps + 1;
                enqueue(nx, ny, steps + 1);
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int result = minSteps();
    if (result == -1) {
        printf("NEVER\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}