#include <stdio.h>
#include <stdlib.h>

#define MAX_W 500
#define MAX_L 500

int W, L;
int heights[MAX_L][MAX_W];

void dfs(int x, int y, int height) {
    if (x < 0 || x >= W || y < 0 || y >= L || heights[y][x] < height) return;
    heights[y][x] = -1;
    dfs(x + 1, y, height);
    dfs(x - 1, y, height);
    dfs(x, y + 1, height);
    dfs(x, y - 1, height);
}

int main() {
    scanf("%d %d", &W, &L);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &heights[i][j]);
        }
    }

    int cable_count = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            if (heights[i][j] != -1) {
                cable_count++;
                dfs(j, i, heights[i][j]);
            }
        }
    }

    printf("%d\n", cable_count);

    return 0;
}