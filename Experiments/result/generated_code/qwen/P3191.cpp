#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 21
#define INF 999999

int N, M;
char grid[MAXN][MAXN];
int doorX, doorY;
int dist[MAXN][MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }
    dist[doorX][doorY] = 0;
    int queueX[MAXN * MAXN], queueY[MAXN * MAXN];
    int front = 0, rear = 0;
    queueX[rear++] = doorX;
    queueY[rear++] = doorY;

    while (front != rear) {
        int x = queueX[front++];
        int y = queueY[front++];
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != 'X' && dist[nx][ny] == INF) {
                dist[nx][ny] = dist[x][y] + 1;
                queueX[rear++] = nx;
                queueY[rear++] = ny;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'D') {
                doorX = i;
                doorY = j;
            }
        }
    }

    bfs();

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') {
                ans = dist[i][j];
                break;
            }
        }
        if (ans > 0) break;
    }

    if (ans > 0) printf("%d\n", ans);
    else printf("impossible\n");

    return 0;
}