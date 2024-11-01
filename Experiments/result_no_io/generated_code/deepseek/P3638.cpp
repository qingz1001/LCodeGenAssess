#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 9
#define MAX_W 500
#define MAX_H 500

typedef struct {
    int x, y;
} Point;

typedef struct {
    int min_robot, max_robot;
} RobotRange;

typedef struct {
    int x, y, direction;
} State;

int n, w, h;
char grid[MAX_H][MAX_W];
Point robot_positions[MAX_N + 1];
int dp[MAX_N + 1][MAX_N + 1][MAX_W][MAX_H];
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int is_valid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w && grid[x][y] != 'x';
}

int bfs(RobotRange range, Point start) {
    int visited[MAX_W][MAX_H];
    memset(visited, 0, sizeof(visited));
    State queue[MAX_W * MAX_H];
    int front = 0, rear = 0;
    queue[rear++] = (State){start.x, start.y, -1};
    visited[start.x][start.y] = 1;
    int steps = 0;

    while (front < rear) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            State current = queue[front++];
            int x = current.x, y = current.y, dir = current.direction;

            if (grid[x][y] >= '1' && grid[x][y] <= '9') {
                int robot_id = grid[x][y] - '0';
                if (robot_id >= range.min_robot && robot_id <= range.max_robot) {
                    return steps;
                }
            }

            for (int d = 0; d < 4; d++) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                if (is_valid(nx, ny) && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    queue[rear++] = (State){nx, ny, d};
                }
            }

            if (dir != -1) {
                int nx = x + directions[dir][0];
                int ny = y + directions[dir][1];
                if (is_valid(nx, ny) && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    queue[rear++] = (State){nx, ny, dir};
                }
            }
        }
        steps++;
    }

    return INT_MAX;
}

int solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            for (int x = 0; x < h; x++) {
                for (int y = 0; y < w; y++) {
                    dp[i][j][x][y] = INT_MAX;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i][robot_positions[i].x][robot_positions[i].y] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            for (int x = 0; x < h; x++) {
                for (int y = 0; y < w; y++) {
                    for (int k = i; k < j; k++) {
                        dp[i][j][x][y] = min(dp[i][j][x][y], dp[i][k][x][y] + dp[k + 1][j][x][y]);
                    }
                    if (dp[i][j][x][y] != INT_MAX) {
                        dp[i][j][x][y] += bfs((RobotRange){i, j}, (Point){x, y});
                    }
                }
            }
        }
    }

    int result = INT_MAX;
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            result = min(result, dp[1][n][x][y]);
        }
    }

    return result == INT_MAX ? -1 : result;
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < w; j++) {
            if (grid[i][j] >= '1' && grid[i][j] <= '9') {
                int robot_id = grid[i][j] - '0';
                robot_positions[robot_id] = (Point){i, j};
            }
        }
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}