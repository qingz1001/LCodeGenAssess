#include <stdio.h>
#include <string.h>

#define MAX 100

int n, m;
char grid[MAX][MAX+1];
int visited[MAX][MAX];

int dx[] = {-2, -1, 0, 1, 2, -1, 0, 1, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2};
int dy[] = {0, -1, -2, -1, 0, 1, 2, 1, 1, 2, -1, -2, -1, 2, 1, 0, -1, 0};

void dfs(int x, int y){
    visited[x][y] = 1;
    for(int k=0; k<18; k++){
        int nx = x + dx[k];
        int ny = y + dy[k];
        if(nx >=0 && nx <n && ny >=0 && ny <m && grid[nx][ny] == '#' && !visited[nx][ny]){
            int dist = abs(nx - x) + abs(ny - y);
            if(dist <=2){
                dfs(nx, ny);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    getchar(); // consume newline
    for(int i=0; i<n; i++){
        fgets(grid[i], MAX+1, stdin);
        // Remove possible newline at the end
        int len = strlen(grid[i]);
        if(grid[i][len-1] == '\n') grid[i][len-1] = '\0';
    }
    memset(visited, 0, sizeof(visited));
    int s=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j] == '#' && !visited[i][j]){
                s++;
                dfs(i,j);
            }
        }
    }
    printf("%d\n", s);
    return 0;
}