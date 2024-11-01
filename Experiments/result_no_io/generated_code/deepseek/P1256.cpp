#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 182

int screen[MAX][MAX];
int distances[MAX][MAX];
int queue[MAX * MAX][2];
int front = 0, rear = 0;

void enqueue(int x, int y) {
    queue[rear][0] = x;
    queue[rear][1] = y;
    rear++;
}

void dequeue(int *x, int *y) {
    *x = queue[front][0];
    *y = queue[front][1];
    front++;
}

int isEmpty() {
    return front == rear;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &screen[i][j]);
            distances[i][j] = INT_MAX;
            if (screen[i][j] == 1) {
                enqueue(i, j);
                distances[i][j] = 0;
            }
        }
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!isEmpty()) {
        int x, y;
        dequeue(&x, &y);

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (distances[nx][ny] > distances[x][y] + 1) {
                    distances[nx][ny] = distances[x][y] + 1;
                    enqueue(nx, ny);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", distances[i][j]);
        }
        printf("\n");
    }

    return 0;
}