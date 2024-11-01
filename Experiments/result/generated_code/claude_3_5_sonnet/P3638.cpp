#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 9
#define MAX_WH 500
#define INF 0x3f3f3f3f

int n, w, h;
char map[MAX_WH][MAX_WH];
int robot_x[MAX_N + 1], robot_y[MAX_N + 1];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

bool is_valid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w && map[x][y] != 'x';
}

void move_robot(int id, int dir) {
    int x = robot_x[id], y = robot_y[id];
    while (is_valid(x + dx[dir], y + dy[dir])) {
        x += dx[dir];
        y += dy[dir];
        if (map[x][y] == 'A') dir = (dir + 3) % 4;
        if (map[x][y] == 'C') dir = (dir + 1) % 4;
    }
    robot_x[id] = x;
    robot_y[id] = y;
}

int merge_robots() {
    int merged = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (robot_x[i] == robot_x[j] && robot_y[i] == robot_y[j]) {
                robot_x[i] = robot_x[j] = min(robot_x[i], robot_x[j]);
                robot_y[i] = robot_y[j] = min(robot_y[i], robot_y[j]);
                merged = 1;
            }
        }
    }
    return merged;
}

int dfs(int step, int last_robot, int last_dir) {
    int all_merged = 1;
    for (int i = 2; i <= n; i++) {
        if (robot_x[i] != robot_x[1] || robot_y[i] != robot_y[1]) {
            all_merged = 0;
            break;
        }
    }
    if (all_merged) return step;

    int result = INF;
    for (int i = 1; i <= n; i++) {
        if (i == last_robot) continue;
        for (int dir = 0; dir < 4; dir++) {
            if (i == last_robot && dir == last_dir) continue;
            int orig_x = robot_x[i], orig_y = robot_y[i];
            move_robot(i, dir);
            if (robot_x[i] == orig_x && robot_y[i] == orig_y) continue;
            if (merge_robots()) {
                int next = dfs(step + 1, i, dir);
                result = min(result, next);
            }
            robot_x[i] = orig_x;
            robot_y[i] = orig_y;
        }
    }
    return result;
}

int main() {
    scanf("%d %d %d", &n, &w, &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] >= '1' && map[i][j] <= '9') {
                int id = map[i][j] - '0';
                robot_x[id] = i;
                robot_y[id] = j;
            }
        }
    }

    int result = dfs(0, 0, -1);
    printf("%d\n", result == INF ? -1 : result);
    return 0;
}