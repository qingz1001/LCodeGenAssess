#include <stdio.h>
#include <string.h>

#define MAX_N 100

int n, m, k;
int grid[MAX_N][MAX_N];

void place_torch(int x, int y) {
    int dx[] = {-2, -2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2};
    int dy[] = {0, 0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0, 0};
    
    for (int i = 0; i < 15; i++) {
        int nx = x + dx[i] - 1, ny = y + dy[i] - 1;
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            grid[nx][ny] = 1;
        }
    }
}

void place_glowstone(int x, int y) {
    for (int i = x - 3; i <= x + 1; i++) {
        for (int j = y - 3; j <= y + 1; j++) {
            if (i >= 0 && i < n && j >= 0 && j < n) {
                grid[i][j] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    memset(grid, 0, sizeof(grid));
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        place_torch(x, y);
    }
    
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        place_glowstone(x, y);
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}