#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_H 30
#define MAX_W 30
#define INF 999999

int h, w;
char map[MAX_H][MAX_W];
int start_x, start_y, start_dir;
int end_x, end_y;

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int cost[4] = {1, 5, 5, 5};

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs(int x, int y, int d, int total_cost) {
    if (x == end_x && y == end_y) {
        printf("%d\n", total_cost);
        exit(0);
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        int nd = (d + i) % 4;
        if (nx >= 0 && nx < h && ny >= 0 && ny < w && map[nx][ny] != '.' && abs(nd - d) <= 1) {
            dfs(nx, ny, nd, total_cost + cost[(i + d) % 4]);
        } else if (abs(nd - d) == 2) {
            dfs(x, y, nd, total_cost + 10);
        }
    }
}

int main() {
    scanf("%d %d", &h, &w);
    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'E') {
                start_x = i;
                start_y = j;
                start_dir = 0;
            } else if (map[i][j] == 'W') {
                start_x = i;
                start_y = j;
                start_dir = 2;
            } else if (map[i][j] == 'N') {
                start_x = i;
                start_y = j;
                start_dir = 3;
            } else if (map[i][j] == 'S') {
                start_x = i;
                start_y = j;
                start_dir = 1;
            } else if (map[i][j] == 'F') {
                end_x = i;
                end_y = j;
            }
        }
    }
    dfs(start_x, start_y, start_dir, 0);
    return 0;
}