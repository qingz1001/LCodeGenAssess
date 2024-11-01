#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXA 100001
#define MAXB 100001

int n, m, a, b;
int sources[MAXA][2];
int leaders[MAXB][2];
int dist[MAXN][MAXN];

void bfs() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dist[i][j] = -1;
        }
    }

    int queue[MAXA * 2][2];
    int front = 0, rear = 0;

    for (int i = 0; i < a; ++i) {
        int x = sources[i][0], y = sources[i][1];
        dist[x][y] = 0;
        queue[rear][0] = x;
        queue[rear++][1] = y;
    }

    while (front != rear) {
        int x = queue[front][0], y = queue[front++][1];
        if (x > 0 && dist[x-1][y] == -1) {
            dist[x-1][y] = dist[x][y] + 1;
            queue[rear][0] = x-1;
            queue[rear++][1] = y;
        }
        if (x < n-1 && dist[x+1][y] == -1) {
            dist[x+1][y] = dist[x][y] + 1;
            queue[rear][0] = x+1;
            queue[rear++][1] = y;
        }
        if (y > 0 && dist[x][y-1] == -1) {
            dist[x][y-1] = dist[x][y] + 1;
            queue[rear][0] = x;
            queue[rear++][1] = y-1;
        }
        if (y < m-1 && dist[x][y+1] == -1) {
            dist[x][y+1] = dist[x][y] + 1;
            queue[rear][0] = x;
            queue[rear++][1] = y+1;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    for (int i = 0; i < a; ++i) {
        scanf("%d %d", &sources[i][0], &sources[i][1]);
    }
    for (int i = 0; i < b; ++i) {
        scanf("%d %d", &leaders[i][0], &leaders[i][1]);
    }

    bfs();

    for (int i = 0; i < b; ++i) {
        printf("%d\n", dist[leaders[i][0]][leaders[i][1]]);
    }

    return 0;
}