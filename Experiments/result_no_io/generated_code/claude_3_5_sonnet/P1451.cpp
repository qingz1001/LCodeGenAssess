#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

char grid[MAX_N][MAX_M + 1];
int n, m;
int visited[MAX_N][MAX_M];

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == '0') {
        return;
    }
    
    visited[x][y] = 1;
    
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

int count_cells() {
    int count = 0;
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j] != '0') {
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
    
    int result = count_cells();
    printf("%d\n", result);
    
    return 0;
}