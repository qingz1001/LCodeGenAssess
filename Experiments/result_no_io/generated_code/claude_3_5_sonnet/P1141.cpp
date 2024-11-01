#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 100000

char maze[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int n, m;
int count;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y]) {
        return;
    }
    
    visited[x][y] = 1;
    count++;
    
    char target = (maze[x][y] == '0') ? '1' : '0';
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && maze[nx][ny] == target) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    
    for (int q = 0; q < m; q++) {
        int i, j;
        scanf("%d %d", &i, &j);
        i--; j--;  // 转换为0-based索引
        
        memset(visited, 0, sizeof(visited));
        count = 0;
        dfs(i, j);
        
        printf("%d\n", count);
    }
    
    return 0;
}