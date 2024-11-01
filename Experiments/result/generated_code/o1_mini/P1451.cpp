#include <stdio.h>
#include <string.h>

#define MAX 100

int n, m;
char grid[MAX][101];
int visited[MAX][MAX];

// Directions: up, down, left, right
int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

void dfs(int x, int y){
    visited[x][y] = 1;
    for(int i=0;i<4;i++){
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];
        if(nx >=0 && nx < n && ny >=0 && ny < m && !visited[nx][ny] && grid[nx][ny]!='0'){
            dfs(nx, ny);
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++){
        scanf("%s", grid[i]);
    }
    memset(visited, 0, sizeof(visited));
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]!='0' && !visited[i][j]){
                count++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", count);
    return 0;
}