#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define INF 0x3f3f3f3f

int M, N;
int grid[MAX][MAX];
int dist[MAX][MAX];
long long ways[MAX][MAX];
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

typedef struct {
    int x, y;
} Point;

void bfs(int sx, int sy) {
    Point queue[MAX * MAX];
    int front = 0, rear = 0;
    memset(dist, INF, sizeof(dist));
    memset(ways, 0, sizeof(ways));

    queue[rear++] = (Point){sx, sy};
    dist[sx][sy] = 0;
    ways[sx][sy] = 1;

    while (front < rear) {
        Point p = queue[front++];
        for (int i = 0; i < 8; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && grid[nx][ny] != 2) {
                if (dist[nx][ny] == INF) {
                    dist[nx][ny] = dist[p.x][p.y] + 1;
                    ways[nx][ny] = ways[p.x][p.y];
                    queue[rear++] = (Point){nx, ny};
                } else if (dist[nx][ny] == dist[p.x][p.y] + 1) {
                    ways[nx][ny] += ways[p.x][p.y];
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
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 4) {
                ex = i;
                ey = j;
            }
        }
    }

    if (sx == -1 || sy == -1 || ex == -1 || ey == -1) {
        printf("-1\n");
        return 0;
    }

    bfs(sx, sy);

    if (dist[ex][ey] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n%lld\n", dist[ex][ey] - 1, ways[ex][ey]);
    }

    return 0;
}