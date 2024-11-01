#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define MAXK 100000

int n, m, k;
int height[MAXN][MAXN];
int visited[MAXN][MAXN];
int minDist[MAXK];

typedef struct {
    int x, y;
} Babingbaboom;

Babingbaboom babingbabooms[MAXK];

int isPeak(int i, int j) {
    int height = this->height[i][j];
    if (i > 0 && this->height[i-1][j] >= height) return 0;
    if (i < n-1 && this->height[i+1][j] >= height) return 0;
    if (j > 0 && this->height[i][j-1] >= height) return 0;
    if (j < m-1 && this->height[i][j+1] >= height) return 0;
    return 1;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void bfs(int startX, int startY) {
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    int dist = 0;
    int queue[MAXN*MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = startX;
    queue[rear][1] = startY;
    visited[startX][startY] = 1;
    while (front <= rear) {
        int size = rear - front + 1;
        for (int i = 0; i < size; i++) {
            int x = queue[front][0];
            int y = queue[front][1];
            front++;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                    if (isPeak(nx, ny)) {
                        minDist[k] = min(minDist[k], abs(startX - nx));
                    } else {
                        queue[++rear][0] = nx;
                        queue[rear][1] = ny;
                        visited[nx][ny] = 1;
                    }
                }
            }
        }
        dist++;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &height[i][j]);
        }
    }
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &babingbabooms[i].x, &babingbabooms[i].y);
        minDist[i] = n + m; // Initialize with maximum possible distance
    }
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < k; i++) {
        if (!visited[babingbabooms[i].x][babingbabooms[i].y]) {
            bfs(babingbabooms[i].x, babingbabooms[i].y);
        }
    }
    for (int i = 0; i < k; i++) {
        if (minDist[i] == n + m) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", minDist[i]);
        }
    }
    return 0;
}