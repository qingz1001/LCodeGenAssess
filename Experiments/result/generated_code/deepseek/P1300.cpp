#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 30

typedef struct {
    int x, y, cost, dir;
} State;

int h, w;
char map[MAX][MAX];
int dx[] = {0, 1, 0, -1}; // N, E, S, W
int dy[] = {-1, 0, 1, 0};
int costs[] = {1, 5, 10}; // Left, Right, Turn

int minCost = INT_MAX;

void dfs(int x, int y, int dir, int cost) {
    if (map[y][x] == 'F') {
        if (cost < minCost) minCost = cost;
        return;
    }

    map[y][x] = '.'; // Mark as visited

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < w && ny >= 0 && ny < h && map[ny][nx] != '.') {
            int turnCost = 0;
            if (i == dir) {
                // Move forward
                dfs(nx, ny, dir, cost);
            } else if ((dir + 1) % 4 == i) {
                // Turn right
                dfs(nx, ny, i, cost + costs[1]);
            } else if ((dir + 3) % 4 == i) {
                // Turn left
                dfs(nx, ny, i, cost + costs[0]);
            } else {
                // Turn around
                dfs(nx, ny, i, cost + costs[2]);
            }
        }
    }

    map[y][x] = '#'; // Unmark for backtracking
}

int main() {
    scanf("%d %d", &h, &w);
    int startX, startY, startDir;

    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'E') {
                startX = j; startY = i; startDir = 1;
            } else if (map[i][j] == 'W') {
                startX = j; startY = i; startDir = 3;
            } else if (map[i][j] == 'N') {
                startX = j; startY = i; startDir = 0;
            } else if (map[i][j] == 'S') {
                startX = j; startY = i; startDir = 2;
            }
        }
    }

    dfs(startX, startY, startDir, 0);
    printf("%d\n", minCost);

    return 0;
}