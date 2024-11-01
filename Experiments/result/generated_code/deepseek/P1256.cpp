#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 182

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int screen[MAX][MAX];
    int distances[MAX][MAX];
    int queue[MAX * MAX][2];
    int front = 0, rear = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &screen[i][j]);
            distances[i][j] = INT_MAX;
            if (screen[i][j] == 1) {
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
                distances[i][j] = 0;
            }
        }
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (distances[nx][ny] > distances[x][y] + 1) {
                    distances[nx][ny] = distances[x][y] + 1;
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
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