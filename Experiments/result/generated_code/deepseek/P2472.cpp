#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXN 25
#define INF 0x3f3f3f3f

int r, c, d;
int height[MAXN][MAXN];
char grid[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Point;

Point lizards[MAXN * MAXN];
int lizard_count = 0;

int dist[MAXN][MAXN][MAXN][MAXN];

void bfs(int sx, int sy) {
    int queue[MAXN * MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    rear++;
    dist[sx][sy][sx][sy] = 0;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < r && ny >= 0 && ny < c && height[nx][ny] > 0 && dist[sx][sy][nx][ny] == INF) {
                dist[sx][sy][nx][ny] = dist[sx][sy][x][y] + 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%1d", &height[i][j]);
        }
    }
    for (int i = 0; i < r; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'L') {
                lizards[lizard_count].x = i;
                lizards[lizard_count].y = j;
                lizard_count++;
            }
        }
    }

    memset(dist, INF, sizeof(dist));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (height[i][j] > 0) {
                bfs(i, j);
            }
        }
    }

    int trapped_lizards = 0;

    for (int i = 0; i < lizard_count; i++) {
        int x = lizards[i].x;
        int y = lizards[i].y;
        bool can_escape = false;

        for (int j = 0; j < r; j++) {
            for (int k = 0; k < c; k++) {
                if (dist[x][y][j][k] <= d && (j == 0 || j == r - 1 || k == 0 || k == c - 1)) {
                    can_escape = true;
                    break;
                }
            }
            if (can_escape) break;
        }

        if (!can_escape) {
            trapped_lizards++;
        }
    }

    printf("%d\n", trapped_lizards);

    return 0;
}