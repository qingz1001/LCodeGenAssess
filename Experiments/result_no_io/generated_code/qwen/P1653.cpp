#include <stdio.h>
#include <stdlib.h>

#define MAX_W 500
#define MAX_L 500

int W, L;
int height[MAX_L][MAX_W];
int visited[MAX_L][MAX_W];

void dfs(int x, int y) {
    if (x < 0 || x >= L || y < 0 || y >= W || visited[x][y]) return;
    visited[x][y] = 1;
    if (x > 0 && height[x-1][y] <= height[x][y]) dfs(x-1, y);
    if (x < L-1 && height[x+1][y] <= height[x][y]) dfs(x+1, y);
    if (y > 0 && height[x][y-1] <= height[x][y]) dfs(x, y-1);
    if (y < W-1 && height[x][y+1] <= height[x][y]) dfs(x, y+1);
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    int cable_cars = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            if (!visited[i][j]) {
                dfs(i, j);
                cable_cars++;
            }
        }
    }

    printf("%d\n", cable_cars);

    return 0;
}