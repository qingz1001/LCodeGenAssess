#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 500
#define MAXM 500

int N, M;
int grid[MAXN][MAXM];
bool visited[MAXN][MAXM];
bool canReach[MAXN][MAXM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y;
} Point;

void bfs(int x, int y) {
    Point queue[MAXN * MAXM];
    int front = 0, rear = 0;
    queue[rear++] = (Point){x, y};
    visited[x][y] = true;

    while (front < rear) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && grid[nx][ny] < grid[p.x][p.y]) {
                visited[nx][ny] = true;
                canReach[nx][ny] = true;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    for (int j = 0; j < M; j++) {
        if (!visited[0][j]) {
            bfs(0, j);
        }
    }

    int unreachableCount = 0;
    for (int j = 0; j < M; j++) {
        if (!canReach[N-1][j]) {
            unreachableCount++;
        }
    }

    if (unreachableCount > 0) {
        printf("0\n%d\n", unreachableCount);
    } else {
        int minWaterStations = 0;
        for (int j = 0; j < M; j++) {
            if (canReach[0][j]) {
                minWaterStations++;
            }
        }
        printf("1\n%d\n", minWaterStations);
    }

    return 0;
}