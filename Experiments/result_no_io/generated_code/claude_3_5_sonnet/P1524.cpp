#include <stdio.h>
#include <string.h>

#define MAX_N 205
#define MAX_M 205

char front[MAX_N][MAX_M], back[MAX_N][MAX_M];
int n, m, visited[MAX_N][MAX_M][2];
int dx[] = {-1, -1, 1, 1};
int dy[] = {-1, 1, -1, 1};

int dfs(int x, int y, int side) {
    if (x < 0 || x >= n || y < 0 || y >= m) return 0;
    if (visited[x][y][side]) return 0;
    
    visited[x][y][side] = 1;
    char (*current)[MAX_M] = side ? back : front;
    int count = 0;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        
        if ((i == 0 || i == 3) && (current[x][y] == '/' || current[x][y] == 'X'))
            count += dfs(nx, ny, !side);
        if ((i == 1 || i == 2) && (current[x][y] == '\\' || current[x][y] == 'X'))
            count += dfs(nx, ny, !side);
    }
    
    return count ? count : 1;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++)
        scanf("%s", front[i]);
    for (int i = 0; i < n; i++)
        scanf("%s", back[i]);
    
    int result = 0;
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((front[i][j] != '.' && !visited[i][j][0]) || (back[i][j] != '.' && !visited[i][j][1]))
                result += dfs(i, j, front[i][j] != '.');
    
    printf("%d\n", result);
    return 0;
}