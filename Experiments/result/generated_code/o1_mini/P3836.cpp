#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int m, n, k;
char grid[MAX][MAX + 1];
char output_grid[MAX][MAX + 1];
int visited[MAX][MAX];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void dfs(int x, int y) {
    visited[x][y] = 1;
    output_grid[x][y] = '.';
    for(int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(nx >=0 && nx < m && ny >=0 && ny < n && grid[nx][ny] == '.' && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main(){
    scanf("%d %d %d", &m, &n, &k);
    for(int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
        strcpy(output_grid[i], grid[i]);
    }

    // Find first empty cell
    int start_x = -1, start_y = -1;
    for(int i =0;i<m;i++) {
        for(int j=0;j<n;j++) {
            if(grid[i][j] == '.') {
                start_x = i;
                start_y = j;
                break;
            }
        }
        if(start_x != -1) break;
    }

    if(start_x != -1 && start_y != -1){
        dfs(start_x, start_y);
    }

    // Convert unused '.' to 'X'
    for(int i =0;i<m;i++) {
        for(int j=0;j<n;j++) {
            if(output_grid[i][j] == '.' && !visited[i][j]) {
                output_grid[i][j] = 'X';
            }
        }
    }

    // Print the output grid
    for(int i=0;i<m;i++) {
        printf("%s\n", output_grid[i]);
    }

    return 0;
}