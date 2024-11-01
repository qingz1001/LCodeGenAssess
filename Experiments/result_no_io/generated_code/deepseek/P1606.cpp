#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_M 30
#define MAX_N 30
#define INF INT_MAX

int M, N;
int pond[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
long long ways[MAX_M][MAX_N];

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

typedef struct {
    int x, y;
} Point;

void bfs(int sx, int sy) {
    Point queue[MAX_M * MAX_N];
    int front = 0, rear = 0;
    queue[rear++] = (Point){sx, sy};
    dist[sx][sy] = 0;
    ways[sx][sy] = 1;

    while (front < rear) {
        Point p = queue[front++];
        int x = p.x, y = p.y;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N && pond[nx][ny] != 2) {
                int new_dist = dist[x][y] + (pond[nx][ny] == 0 ? 1 : 0);

                if (new_dist < dist[nx][ny]) {
                    dist[nx][ny] = new_dist;
                    ways[nx][ny] = ways[x][y];
                    queue[rear++] = (Point){nx, ny};
                } else if (new_dist == dist[nx][ny]) {
                    ways[nx][ny] += ways[x][y];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &M, &N);
    int sx = -1, sy = -1, ex = -1, ey = -1;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                sx = i;
                sy = j;
            } else if (pond[i][j] == 4) {
                ex = i;
                ey = j;
            }
            dist[i][j] = INF;
            ways[i][j] = 0;
        }
    }

    bfs(sx, sy);

    if (dist[ex][ey] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n%lld\n", dist[ex][ey], ways[ex][ey]);
    }

    return 0;
}