#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100
#define INF INT_MAX

char grid[MAX_N][MAX_N];
int dist[MAX_N][MAX_N][4];
int N;

typedef struct {
    int x, y, dir;
} State;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

State queue[MAX_N * MAX_N * 4];
int front, rear;

void enqueue(State s) {
    queue[rear++] = s;
}

State dequeue() {
    return queue[front++];
}

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    front = rear = 0;

    for (int i = 0; i < 4; i++) {
        dist[sx][sy][i] = 0;
        enqueue((State){sx, sy, i});
    }

    while (front < rear) {
        State cur = dequeue();
        int x = cur.x, y = cur.y, dir = cur.dir;

        if (x == ex && y == ey) {
            return dist[x][y][dir];
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x') {
                int turns = (i == dir) ? 0 : 1;
                if (dist[nx][ny][i] > dist[x][y][dir] + turns) {
                    dist[nx][ny][i] = dist[x][y][dir] + turns;
                    enqueue((State){nx, ny, i});
                }
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d", &N);
    int sx, sy, ex, ey;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'A') {
                sx = i; sy = j;
            } else if (grid[i][j] == 'B') {
                ex = i; ey = j;
            }
        }
    }

    int result = bfs(sx, sy, ex, ey);
    printf("%d\n", result);

    return 0;
}