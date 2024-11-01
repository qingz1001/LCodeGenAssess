#include <stdio.h>
#include <string.h>

#define MAX 100

int n, m;
char grid[MAX][MAX + 1];
int visited[MAX][MAX];

// Directions with Manhattan distance <=2
int dx[] = {-2, -1, -1, -1, 0, 0, 1, 1, 1, 2};
int dy[] = {0, -1, 1, 2, -2, 2, -1, 1, 2, 0};

void dfs(int x, int y) {
    visited[x][y] = 1;
    for(int i=0;i<10;i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >=0 && nx < n && ny >=0 && ny < m && !visited[nx][ny] && grid[nx][ny] == '#') {
            dfs(nx, ny);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    memset(visited, 0, sizeof(visited));
    int s =0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(grid[i][j] == '#' && !visited[i][j]){
                dfs(i,j);
                s++;
            }
        }
    }
    printf("%d\n", s);
    return 0;
}