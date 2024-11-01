#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1000
#define MAX_M 1000

char grid[MAX_N][MAX_M + 1];
int N, M, Q;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool visited[MAX_N][MAX_M];

void dfs(int x, int y, char color, int x1, int y1, int x2, int y2) {
    if (x < x1 || x > x2 || y < y1 || y > y2 || visited[x][y] || grid[x][y] != color) {
        return;
    }
    
    visited[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        dfs(nx, ny, color, x1, y1, x2, y2);
    }
}

int count_strokes(int x1, int y1, int x2, int y2) {
    memset(visited, 0, sizeof(visited));
    int strokes = 0;
    
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (!visited[i][j]) {
                dfs(i, j, grid[i][j], x1, y1, x2, y2);
                strokes++;
            }
        }
    }
    
    return strokes;
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    
    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }
    
    for (int q = 0; q < Q; q++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;  // 转换为0-based索引
        printf("%d\n", count_strokes(x1, y1, x2, y2));
    }
    
    return 0;
}