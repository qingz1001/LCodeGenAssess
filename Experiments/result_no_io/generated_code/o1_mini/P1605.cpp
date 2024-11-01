#include <stdio.h>

int N, M, T;
int grid[5][5];
int visited[5][5];
int SX, SY, FX, FY;
int count_paths = 0;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if(x == FX && y == FY){
        count_paths++;
        return;
    }
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >=0 && nx < N && ny >=0 && ny < M && !grid[nx][ny] && !visited[nx][ny]){
            visited[nx][ny] = 1;
            dfs(nx, ny);
            visited[nx][ny] = 0;
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &SX, &SY, &FX, &FY);
    // Initialize grid to 0
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            grid[i][j] = 0;
    // Read obstacles
    for(int i=0;i<T;i++){
        int ox, oy;
        scanf("%d %d", &ox, &oy);
        grid[ox-1][oy-1] = 1;
    }
    // Adjust to 0-based
    SX -=1;
    SY -=1;
    FX -=1;
    FY -=1;
    if(grid[SX][SY]){
        printf("0");
        return 0;
    }
    visited[SX][SY] = 1;
    dfs(SX, SY);
    printf("%d", count_paths);
    return 0;
}