#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000

int map[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
int n, m, k;

typedef struct {
    int x, y;
} Point;

int isPeak(int x, int y) {
    int height = map[x][y];
    if (x > 0 && map[x-1][y] >= height) return 0;
    if (x < n-1 && map[x+1][y] >= height) return 0;
    if (y > 0 && map[x][y-1] >= height) return 0;
    if (y < m-1 && map[x][y+1] >= height) return 0;
    return 1;
}

void bfs(Point start) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    Point queue[MAX_N * MAX_M];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start.x][start.y] = 1;
    dist[start.x][start.y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[current.x][current.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    Point peaks[MAX_N * MAX_M];
    int peakCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isPeak(i, j)) {
                peaks[peakCount++] = (Point){i, j};
            }
        }
    }

    for (int i = 0; i < peakCount; i++) {
        bfs(peaks[i]);
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (dist[x-1][y-1] == 0) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", dist[x-1][y-1]);
        }
    }

    return 0;
}