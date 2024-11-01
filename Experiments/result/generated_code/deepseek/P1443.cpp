#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 400

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

typedef struct {
    int x, y;
} Point;

void bfs(int n, int m, int x, int y, int **dist) {
    Point queue[MAX * MAX];
    int front = 0, rear = 0;
    queue[rear++] = (Point){x, y};
    dist[x][y] = 0;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[current.x][current.y] + 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    int **dist = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dist[i][j] = -1;
        }
    }

    bfs(n, m, x - 1, y - 1, dist);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);

    return 0;
}