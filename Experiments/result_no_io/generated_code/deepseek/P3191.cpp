#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 20
#define MAXM 20
#define INF INT_MAX

typedef struct {
    int x, y;
} Point;

int N, M;
char grid[MAXN][MAXM];
int dist[MAXN][MAXM][MAXN][MAXM];
Point doors[MAXN * MAXM];
int door_count = 0;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int sx, int sy) {
    int queue[MAXN * MAXM][2];
    int front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    rear++;
    dist[sx][sy][sx][sy] = 0;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != 'X' && dist[sx][sy][nx][ny] == INF) {
                dist[sx][sy][nx][ny] = dist[sx][sy][x][y] + 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
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
                doors[door_count].x = i;
                doors[door_count].y = j;
                door_count++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < M; l++) {
                    dist[i][j][k][l] = INF;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') {
                bfs(i, j);
            }
        }
    }

    int min_time = INF;
    for (int d = 0; d < door_count; d++) {
        int max_time = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == '.') {
                    if (dist[i][j][doors[d].x][doors[d].y] == INF) {
                        printf("impossible\n");
                        return 0;
                    }
                    max_time = (max_time > dist[i][j][doors[d].x][doors[d].y]) ? max_time : dist[i][j][doors[d].x][doors[d].y];
                }
            }
        }
        min_time = (min_time < max_time) ? min_time : max_time;
    }

    if (min_time == INF) {
        printf("impossible\n");
    } else {
        printf("%d\n", min_time);
    }

    return 0;
}