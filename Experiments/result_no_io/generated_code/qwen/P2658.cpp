#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 500
#define MAX_M 500

typedef struct {
    int x, y;
} Point;

int N, M;
int heights[MAX_M][MAX_N];
int markers[MAX_M][MAX_N];
Point start, end;

int is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

int bfs(int D) {
    if (start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1) {
        return -1;
    }

    int visited[MAX_M][MAX_N] = {0};
    int queue[MAX_N * MAX_M][2];
    int front = 0, rear = 0;

    queue[rear][0] = start.x;
    queue[rear++][1] = start.y;
    visited[start.x][start.y] = 1;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front++][1];

        if (x == end.x && y == end.y) {
            return 1;
        }

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx * dy == 0 && is_valid(x + dx, y + dy)) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (!visited[nx][ny] && abs(heights[nx][ny] - heights[x][y]) <= D) {
                        queue[rear][0] = nx;
                        queue[rear++][1] = ny;
                        visited[nx][ny] = 1;
                    }
                }
            }
        }
    }

    return 0;
}

int binary_search() {
    int left = 0, right = INT_MAX;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (bfs(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &heights[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &markers[i][j]);
            if (markers[i][j] == 1) {
                if (start.x == -1 && start.y == -1) {
                    start.x = i;
                    start.y = j;
                } else {
                    end.x = i;
                    end.y = j;
                }
            }
        }
    }

    printf("%d\n", binary_search());

    return 0;
}