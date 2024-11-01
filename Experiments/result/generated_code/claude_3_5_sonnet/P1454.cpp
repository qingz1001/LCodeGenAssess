#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

char grid[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int n, m;

int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

void dfs(int x, int y) {
    visited[x][y] = 1;
    
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
            grid[nx][ny] == '#' && !visited[nx][ny] && 
            (abs(nx - x) + abs(ny - y) <= 2)) {
            dfs(nx, ny);
        }
    }
}

int count_patterns() {
    int count = 0;
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    int result = count_patterns();
    printf("%d\n", result);
    
    return 0;
}