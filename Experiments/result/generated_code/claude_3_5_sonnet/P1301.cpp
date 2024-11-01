#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 100
#define INF 0x3f3f3f3f

int N, M;
int map[MAX_N][MAX_M];
int dist[MAX_N][MAX_M][8];
bool visited[MAX_N][MAX_M][8];

int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

typedef struct {
    int x, y, dir, steps;
} State;

State queue[MAX_N * MAX_M * 8];
int front, rear;

void enqueue(int x, int y, int dir, int steps) {
    queue[rear].x = x;
    queue[rear].y = y;
    queue[rear].dir = dir;
    queue[rear].steps = steps;
    rear++;
}

State dequeue() {
    return queue[front++];
}

bool is_empty() {
    return front == rear;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

int bfs() {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));
    front = rear = 0;

    for (int i = 0; i < 8; i++) {
        dist[0][0][i] = 0;
        enqueue(0, 0, i, 0);
    }

    while (!is_empty()) {
        State cur = dequeue();
        int x = cur.x, y = cur.y, dir = cur.dir, steps = cur.steps;

        if (x == N - 1 && y == M - 1) {
            return steps;
        }

        if (visited[x][y][dir]) continue;
        visited[x][y][dir] = true;

        for (int i = 0; i < 8; i++) {
            if (i == dir) continue;
            int nx = x + dx[i] * map[x][y];
            int ny = y + dy[i] * map[x][y];
            if (is_valid(nx, ny) && !visited[nx][ny][i] && dist[nx][ny][i] > steps + 1) {
                dist[nx][ny][i] = steps + 1;
                enqueue(nx, ny, i, steps + 1);
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    int result = bfs();
    if (result == -1) {
        printf("NEVER\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}