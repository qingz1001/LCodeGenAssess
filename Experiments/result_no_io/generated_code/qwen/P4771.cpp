#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXK 100005

int n, m, k;
int h[MAXN][MAXN];
int babingbaboom[MAXK][2];
int visited[MAXN][MAXN];

typedef struct {
    int x, y, dist;
} Point;

void bfs(int startx, int starty) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){startx, starty, 0};
    visited[startx][starty] = 1;

    while (front < rear) {
        Point current = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                if (h[nx][ny] >= h[current.x][current.y]) {
                    continue;
                }
                queue[rear++] = (Point){nx, ny, current.dist + 1};
                visited[nx][ny] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &h[i][j]);
        }
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &babingbaboom[i][0], &babingbaboom[i][1]);
        babingbaboom[i][0]--;
        babingbaboom[i][1]--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && h[i][j] > h[i-1][j] && h[i][j] > h[i+1][j] && h[i][j] > h[i][j-1] && h[i][j] > h[i][j+1]) {
                bfs(i, j);
            }
        }
    }

    for (int i = 0; i < k; i++) {
        if (visited[babingbaboom[i][0]][babingbaboom[i][1]]) {
            printf("%d\n", visited[babingbaboom[i][0]][babingbaboom[i][1]] - 1);
        } else {
            printf("Pool Babingbaboom!\n");
        }
    }

    return 0;
}