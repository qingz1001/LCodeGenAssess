#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_H 30
#define MAX_W 30

typedef struct {
    int x, y, cost, direction;
} State;

int h, w;
char map[MAX_H][MAX_W];
int dx[] = {0, 1, 0, -1}; // N, E, S, W
int dy[] = {-1, 0, 1, 0};

int min_cost = INT_MAX;

int is_valid(int x, int y) {
    return x >= 0 && x < w && y >= 0 && y < h && map[y][x] != '.';
}

void dfs(int x, int y, int cost, int direction) {
    if (map[y][x] == 'F') {
        if (cost < min_cost) {
            min_cost = cost;
        }
        return;
    }

    // Move forward
    int nx = x + dx[direction];
    int ny = y + dy[direction];
    if (is_valid(nx, ny)) {
        dfs(nx, ny, cost, direction);
    }

    // Turn left
    int left_direction = (direction + 3) % 4;
    nx = x + dx[left_direction];
    ny = y + dy[left_direction];
    if (is_valid(nx, ny)) {
        dfs(nx, ny, cost + 1, left_direction);
    }

    // Turn right
    int right_direction = (direction + 1) % 4;
    nx = x + dx[right_direction];
    ny = y + dy[right_direction];
    if (is_valid(nx, ny)) {
        dfs(nx, ny, cost + 5, right_direction);
    }

    // Turn around
    int back_direction = (direction + 2) % 4;
    nx = x + dx[back_direction];
    ny = y + dy[back_direction];
    if (is_valid(nx, ny)) {
        dfs(nx, ny, cost + 10, back_direction);
    }
}

int main() {
    scanf("%d %d", &h, &w);
    int start_x, start_y, start_direction;

    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'E') {
                start_x = j;
                start_y = i;
                start_direction = 1; // E
            } else if (map[i][j] == 'W') {
                start_x = j;
                start_y = i;
                start_direction = 3; // W
            } else if (map[i][j] == 'N') {
                start_x = j;
                start_y = i;
                start_direction = 0; // N
            } else if (map[i][j] == 'S') {
                start_x = j;
                start_y = i;
                start_direction = 2; // S
            }
        }
    }

    dfs(start_x, start_y, 0, start_direction);
    printf("%d\n", min_cost);

    return 0;
}