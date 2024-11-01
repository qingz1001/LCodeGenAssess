#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 500

int N;
int grid[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y;
} Point;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int bfs(int x, int y, int max_diff) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    int count = 0;

    queue[rear++] = (Point){x, y};
    visited[x][y] = true;
    count++;

    while (front < rear) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]) {
                if (abs(grid[nx][ny] - grid[p.x][p.y]) <= max_diff) {
                    queue[rear++] = (Point){nx, ny};
                    visited[nx][ny] = true;
                    count++;
                }
            }
        }
    }

    return count;
}

bool can_visit_half(int max_diff) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                int count = bfs(i, j, max_diff);
                if (count >= (N * N + 1) / 2) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int left = 0, right = 1000000;
    int result = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (can_visit_half(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", result);
    return 0;
}