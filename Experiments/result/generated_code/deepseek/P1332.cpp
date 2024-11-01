#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500
#define MAXM 500

int n, m, a, b;
int grid[MAXN][MAXM];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Point;

void bfs(Point sources[], int num_sources) {
    Point queue[MAXN * MAXM];
    int front = 0, rear = 0;

    for (int i = 0; i < num_sources; i++) {
        queue[rear++] = sources[i];
        grid[sources[i].x][sources[i].y] = 0;
    }

    while (front < rear) {
        Point current = queue[front++];
        int current_time = grid[current.x][current.y];

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == INT_MAX) {
                grid[nx][ny] = current_time + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = INT_MAX;
        }
    }

    Point sources[a];
    for (int i = 0; i < a; i++) {
        scanf("%d %d", &sources[i].x, &sources[i].y);
        sources[i].x--;
        sources[i].y--;
    }

    bfs(sources, a);

    for (int i = 0; i < b; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        printf("%d\n", grid[x][y]);
    }

    return 0;
}