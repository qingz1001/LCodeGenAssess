#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 20
#define INF 1000000000

typedef struct {
    int x, y;
} Point;

int N, M;
char grid[MAX_N][MAX_M];
Point doors[4];
int door_count = 0;
int distances[MAX_N][MAX_M];

void bfs() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            distances[i][j] = INF;
        }
    }

    for (int i = 0; i < door_count; i++) {
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        int x = doors[i].x;
        int y = doors[i].y;
        distances[x][y] = 0;
        int queue[MAX_N * MAX_M];
        int front = 0, rear = 0;
        queue[rear++] = x * M + y;

        while (front != rear) {
            int u = queue[front++];
            int ux = u / M;
            int uy = u % M;

            for (int k = 0; k < 4; k++) {
                int nx = ux + dx[k];
                int ny = uy + dy[k];

                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == '.' && distances[nx][ny] == INF) {
                    distances[nx][ny] = distances[ux][uy] + 1;
                    queue[rear++] = nx * M + ny;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'D') {
                doors[door_count++] = (Point){i, j};
            }
        }
    }

    bfs();

    int max_distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') {
                if (distances[i][j] == INF) {
                    printf("impossible\n");
                    return 0;
                }
                max_distance = fmax(max_distance, distances[i][j]);
            }
        }
    }

    printf("%d\n", max_distance);
    return 0;
}