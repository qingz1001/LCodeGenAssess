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
int dist[MAXN][MAXM];
Point doors[MAXN * MAXM];
int door_count = 0;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(Point door) {
    int queue[MAXN * MAXM];
    int front = 0, rear = 0;
    int visited[MAXN][MAXM] = {0};

    queue[rear++] = door.x * M + door.y;
    visited[door.x][door.y] = 1;
    dist[door.x][door.y] = 0;

    while (front < rear) {
        int cur = queue[front++];
        int x = cur / M;
        int y = cur % M;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == '.' && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[x][y] + 1;
                queue[rear++] = nx * M + ny;
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

    int max_dist = 0;
    for (int i = 0; i < door_count; i++) {
        memset(dist, INF, sizeof(dist));
        bfs(doors[i]);

        for (int x = 0; x < N; x++) {
            for (int y = 0; y < M; y++) {
                if (grid[x][y] == '.') {
                    if (dist[x][y] == INF) {
                        printf("impossible\n");
                        return 0;
                    }
                    max_dist = (dist[x][y] > max_dist) ? dist[x][y] : max_dist;
                }
            }
        }
    }

    printf("%d\n", max_dist);
    return 0;
}