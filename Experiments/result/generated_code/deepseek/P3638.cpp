#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 9
#define MAXW 500
#define MAXH 500

typedef struct {
    int x, y;
} Point;

typedef struct {
    int min_id, max_id;
} Robot;

typedef struct {
    int x, y, dir;
} State;

int n, w, h;
char grid[MAXH][MAXW];
Point positions[MAXN + 1];
int dist[MAXN + 1][MAXN + 1];
int dp[1 << MAXN][MAXN];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(Point start, Point end) {
    int visited[MAXH][MAXW] = {0};
    State queue[MAXW * MAXH];
    int front = 0, rear = 0;
    queue[rear++] = (State){start.x, start.y, 0};
    visited[start.x][start.y] = 1;

    while (front < rear) {
        State curr = queue[front++];
        if (curr.x == end.x && curr.y == end.y) {
            return visited[curr.x][curr.y] - 1;
        }

        int nx = curr.x + dx[curr.dir];
        int ny = curr.y + dy[curr.dir];
        if (nx >= 0 && nx < h && ny >= 0 && ny < w && !visited[nx][ny] && grid[nx][ny] != 'x') {
            if (grid[nx][ny] == 'A') {
                curr.dir = (curr.dir + 3) % 4;
            } else if (grid[nx][ny] == 'C') {
                curr.dir = (curr.dir + 1) % 4;
            }
            queue[rear++] = (State){nx, ny, curr.dir};
            visited[nx][ny] = visited[curr.x][curr.y] + 1;
        }
    }

    return INT_MAX;
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < w; j++) {
            if (grid[i][j] >= '1' && grid[i][j] <= '9') {
                positions[grid[i][j] - '0'] = (Point){i, j};
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dist[i][j] = dist[j][i] = bfs(positions[i], positions[j]);
        }
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INT_MAX;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == INT_MAX) continue;
            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j))) {
                    dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i + 1][j + 1]);
                }
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < n; i++) {
        result = min(result, dp[(1 << n) - 1][i]);
    }

    if (result == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}