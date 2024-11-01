#include <stdio.h>
#include <stdlib.h>

#define MAX_W 501
#define MAX_L 501
#define MAX_HEIGHT 10000

int height[MAX_W][MAX_L];
int visited[MAX_W][MAX_L];
int min_cables = 0;
int W, L;

typedef struct {
    int x;
    int y;
} Point;

Point directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i].x;
        int ny = y + directions[i].y;
        if (nx >= 0 && nx < W && ny >= 0 && ny < L && height[x][y] > height[nx][ny]) {
            if (!visited[nx][ny]) {
                dfs(nx, ny);
            }
        }
    }
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < L; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    for (int i = 0; i < W; i++) {
        for (int j = 0; j < L; j++) {
            if (!visited[i][j]) {
                dfs(i, j);
                min_cables++;
            }
        }
    }

    printf("%d\n", min_cables);
    return 0;
}