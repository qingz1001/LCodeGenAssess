#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 33100

typedef struct {
    int x, y, d;
} Node;

int N, M;
int matrix[182][182];
int dist[182][182];
int visited[182][182];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void bfs(int startX, int startY) {
    Node queue[MAX];
    int front = 0, rear = 0;
    queue[rear].x = startX;
    queue[rear].y = startY;
    queue[rear].d = 0;
    rear++;
    visited[startX][startY] = 1;

    while (front < rear) {
        Node current = queue[front];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                dist[nx][ny] = current.d + 1;
                queue[rear].x = nx;
                queue[rear].y = ny;
                queue[rear].d = current.d + 1;
                rear++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &matrix[i][j]);
            dist[i][j] = MAX;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] == 1) {
                bfs(i, j);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}