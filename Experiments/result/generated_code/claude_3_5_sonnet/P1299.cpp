#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2001
#define OFFSET 1000

int grid[MAX_SIZE][MAX_SIZE];

void cut(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        for (int y = y1; y <= y2 || y >= y2; y += (y2 > y1) ? 1 : -1) {
            grid[x1 + OFFSET][y + OFFSET] = 1;
        }
    } else {
        for (int x = x1; x <= x2 || x >= x2; x += (x2 > x1) ? 1 : -1) {
            grid[x + OFFSET][y1 + OFFSET] = 1;
        }
    }
}

int dfs(int x, int y) {
    if (x < 0 || x >= MAX_SIZE || y < 0 || y >= MAX_SIZE || grid[x][y] == 1) {
        return 0;
    }
    
    grid[x][y] = 1;
    
    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
    
    return 1;
}

int count_holes() {
    int holes = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (grid[i][j] == 0) {
                holes += dfs(i, j);
            }
        }
    }
    return holes - 1;  // Subtract 1 to exclude the outer area
}

int main() {
    int N, x1, y1, x2, y2;
    
    scanf("%d", &N);
    
    memset(grid, 0, sizeof(grid));
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        cut(x1, y1, x2, y2);
    }
    
    printf("%d\n", count_holes());
    
    return 0;
}