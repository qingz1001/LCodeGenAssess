#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

int M, N, P;
int grid[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
int ways[MAX_M][MAX_N];
int max_gold[MAX_M][MAX_N];
int max_gold_ways[MAX_M][MAX_N];
Point start, end;

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

void bfs() {
    memset(dist, INF, sizeof(dist));
    memset(ways, 0, sizeof(ways));
    memset(max_gold, 0, sizeof(max_gold));
    memset(max_gold_ways, 0, sizeof(max_gold_ways));

    Point queue[MAX_M * MAX_N];
    int front = 0, rear = 0;
    queue[rear++] = start;
    dist[start.x][start.y] = 0;
    ways[start.x][start.y] = 1;

    while (front < rear) {
        Point cur = queue[front++];
        for (int i = 0; i < 8; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && grid[nx][ny] != 2) {
                int new_dist = dist[cur.x][cur.y] + (grid[nx][ny] == 5 ? 2 : 1);
                if (new_dist <= P) {
                    if (new_dist < dist[nx][ny]) {
                        dist[nx][ny] = new_dist;
                        ways[nx][ny] = ways[cur.x][cur.y];
                        max_gold[nx][ny] = max_gold[cur.x][cur.y] + (grid[nx][ny] == 5 ? 1 : 0);
                        max_gold_ways[nx][ny] = max_gold_ways[cur.x][cur.y];
                        queue[rear++] = (Point){nx, ny};
                    } else if (new_dist == dist[nx][ny]) {
                        ways[nx][ny] += ways[cur.x][cur.y];
                        if (max_gold[nx][ny] < max_gold[cur.x][cur.y] + (grid[nx][ny] == 5 ? 1 : 0)) {
                            max_gold[nx][ny] = max_gold[cur.x][cur.y] + (grid[nx][ny] == 5 ? 1 : 0);
                            max_gold_ways[nx][ny] = max_gold_ways[cur.x][cur.y];
                        } else if (max_gold[nx][ny] == max_gold[cur.x][cur.y] + (grid[nx][ny] == 5 ? 1 : 0)) {
                            max_gold_ways[nx][ny] += max_gold_ways[cur.x][cur.y];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &P, &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 3) start = (Point){i, j};
            if (grid[i][j] == 4) end = (Point){i, j};
        }
    }

    bfs();

    if (dist[end.x][end.y] == INF) {
        printf("-1\n");
    } else {
        printf("%d %d\n", dist[end.x][end.y], ways[end.x][end.y]);
        if (max_gold[end.x][end.y] == 0) {
            printf("-1\n");
        } else {
            printf("%d %d\n", max_gold[end.x][end.y], max_gold_ways[end.x][end.y]);
        }
    }

    return 0;
}