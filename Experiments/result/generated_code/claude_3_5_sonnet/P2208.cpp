#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 500
#define MAX_M 500

char grid[MAX_N][MAX_M+1];
int dist[MAX_N][MAX_M][2];
int N, M;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y, g, d;
} State;

State queue[MAX_N * MAX_M * 2];
int front, rear;

void enqueue(int x, int y, int g, int d) {
    queue[rear++] = (State){x, y, g, d};
}

State dequeue() {
    return queue[front++];
}

bool is_empty() {
    return front == rear;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && grid[x][y] != '#';
}

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    front = rear = 0;

    enqueue(sx, sy, 0, 0);
    dist[sx][sy][0] = 0;

    while (!is_empty()) {
        State cur = dequeue();
        int x = cur.x, y = cur.y, g = cur.g, d = cur.d;

        if (x == ex && y == ey) return d;

        // Move left or right
        for (int i = 2; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (is_valid(nx, ny) && d < dist[nx][ny][g]) {
                dist[nx][ny][g] = d;
                enqueue(nx, ny, g, d);
            }
        }

        // Fall or flip gravity
        int nx = x + (g ? -1 : 1);
        if (!is_valid(nx, y)) {
            int ng = 1 - g;
            nx = x + (ng ? -1 : 1);
            if (is_valid(nx, y) && d + 1 < dist[nx][y][ng]) {
                dist[nx][y][ng] = d + 1;
                enqueue(nx, y, ng, d + 1);
            }
        } else if (d < dist[nx][y][g]) {
            dist[nx][y][g] = d;
            enqueue(nx, y, g, d);
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    int sx, sy, ex, ey;
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'C') {
                sx = i; sy = j;
            } else if (grid[i][j] == 'D') {
                ex = i; ey = j;
            }
        }
    }

    printf("%d\n", bfs(sx, sy, ex, ey));
    return 0;
}