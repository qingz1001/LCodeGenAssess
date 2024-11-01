#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define INF 1000000

int N;
char grid[MAX_N][MAX_N];
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int bfs(int startX, int startY, int endX, int endY) {
    int dist[MAX_N][MAX_N][4]; // dist[i][j][k]: distance to reach cell (i, j) with direction k
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                dist[i][j][k] = INF;
            }
        }
    }

    dist[startX][startY][0] = 0;

    typedef struct {
        int x, y, dir, steps;
    } State;

    State queue[N * N * 4];
    int front = 0, rear = 0;

    queue[rear++] = (State){startX, startY, 0, 0};

    while (front != rear) {
        State current = queue[front++];
        int cx = current.x, cy = current.y, cdir = current.dir, csteps = current.steps;

        if (cx == endX && cy == endY) {
            return csteps;
        }

        for (int d = 0; d < 4; d++) {
            int nx = cx + directions[d][0];
            int ny = cy + directions[d][1];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x') {
                int ndir = d;
                if (d != cdir) {
                    ndir = (d + 2) % 4;
                    csteps++;
                }

                if (dist[nx][ny][ndir] > csteps) {
                    dist[nx][ny][ndir] = csteps;
                    queue[rear++] = (State){nx, ny, ndir, csteps};
                }
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d", &N);
    int startX, startY, endX, endY;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }

    int result = bfs(startX, startY, endX, endY);
    printf("%d\n", result);

    return 0;
}