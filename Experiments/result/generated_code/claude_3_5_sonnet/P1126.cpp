#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 50
#define MAX_M 50
#define INF INT_MAX

int N, M;
int grid[MAX_N][MAX_M];
int dist[MAX_N][MAX_M][4];
bool visited[MAX_N][MAX_M][4];

int dx[] = {0, 1, 0, -1};  // E, S, W, N
int dy[] = {1, 0, -1, 0};

typedef struct {
    int x, y, dir, time;
} State;

State queue[MAX_N * MAX_M * 4];
int front, rear;

void enqueue(State s) {
    queue[rear++] = s;
}

State dequeue() {
    return queue[front++];
}

bool isEmpty() {
    return front == rear;
}

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && !grid[x][y];
}

int bfs(int sx, int sy, int sdir, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));

    front = rear = 0;
    enqueue((State){sx, sy, sdir, 0});
    dist[sx][sy][sdir] = 0;

    while (!isEmpty()) {
        State cur = dequeue();
        int x = cur.x, y = cur.y, dir = cur.dir, time = cur.time;

        if (x == ex && y == ey) return time;

        if (visited[x][y][dir]) continue;
        visited[x][y][dir] = true;

        // Turn left or right
        for (int i = -1; i <= 1; i += 2) {
            int newDir = (dir + i + 4) % 4;
            if (dist[x][y][newDir] > time + 1) {
                dist[x][y][newDir] = time + 1;
                enqueue((State){x, y, newDir, time + 1});
            }
        }

        // Move forward
        for (int step = 1; step <= 3; step++) {
            int nx = x + dx[dir] * step;
            int ny = y + dy[dir] * step;
            if (!isValid(nx, ny)) break;
            if (dist[nx][ny][dir] > time + 1) {
                dist[nx][ny][dir] = time + 1;
                enqueue((State){nx, ny, dir, time + 1});
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int sx, sy, ex, ey;
    char dir;
    scanf("%d %d %d %d %c", &sx, &sy, &ex, &ey, &dir);
    sx--; sy--; ex--; ey--;

    int sdir;
    switch (dir) {
        case 'E': sdir = 0; break;
        case 'S': sdir = 1; break;
        case 'W': sdir = 2; break;
        case 'N': sdir = 3; break;
    }

    int result = bfs(sx, sy, sdir, ex, ey);
    printf("%d\n", result);

    return 0;
}